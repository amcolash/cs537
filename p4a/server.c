#include "request.h"
#include "cs537.h"
#include <pthread.h>
#include <stdio.h>

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// CS537: Parse the new arguments too
void getargs(int* port, int* thread_cnt, struct thread_info* info, int argc, char* argv[])
{
	if (argc != 4) {
		fprintf(stderr, "Usage: server <portnum> <threads> <buffers>\n");
		exit(1);
	}
	*port = atoi(argv[1]);
	*thread_cnt = atoi(argv[2]);
	info->buffer_size = atoi(argv[3]);
}


void produce(int fd, struct thread_info* info, char* request, int size)
{
    pthread_mutex_lock(info->lock);
    
    // wait till a position becomes empty
    while(info->buff_count == info->buffer_size)
    {
        pthread_cond_wait(info->freed, info->lock);
    }
    
    // place job into a freed queue position
    int i;
    for(i = 0; i < info->buffer_size; i++)
    {
        if(info->buffer[i] == NULL)
        {
            info->buffer[i] = fd;
            info->sizes[i] = size;
            info->requests[i] = request;
            info->buff_count++;
            break;
        }
    }
    pthread_cond_signal(info->filled);	// notify
    
    pthread_mutex_unlock(info->lock);
}

void* consume(void* arg)
{
    char *request;
    int fd;
    
    while(1)
    {

        struct thread_info* info = (struct thread_info*)arg;
        pthread_mutex_lock(info->lock);
        
        // if no requests, wait till a position gets filled
        while (info->buff_count == 0)
        {
            pthread_cond_wait(info->filled, info->lock);
        }
        
        // get next request to serve, based on file size
        int min = 0, i;
        for(i = 1; i < info->buffer_size; i++)
        {
            if(info->buffer[i] != NULL && info->sizes[i] < info->sizes[min])
            {
                min = i;
            }
        }
        
        // copy buffered request to temp variables (before they get cleared)
        fd = info->buffer[min];
        request = info->requests[min];
        info->buffer[min] = NULL;		// clear for next request
        
        info->buff_count--;
        pthread_cond_signal(info->freed);	// notify
        pthread_mutex_unlock(info->lock);
        
        // handle chosen request
        requestHandle(fd, request);
        Close(fd);
    }
}

int getSize(char *buffer)
{
    char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    sscanf(buffer, "%s %s %s", method, uri, version);
    requestParseURI(uri, filename, cgiargs);	// get filename
    
    // find and return file size
    struct stat sbuf;
    if (stat(filename, &sbuf) < 0)
    {
        printf("stat check on %s failed!\n", filename);
        return -1;
    }
    return sbuf.st_size;
}


int main(int argc, char *argv[])
{
	int listenfd, connfd, port, clientlen, thread_cnt;
	struct sockaddr_in clientaddr;
	struct thread_info info;

	getargs(&port, &thread_cnt, &info, argc, argv);

	info.buffer = malloc(sizeof(int) * info.buffer_size);
	info.requests = (char**) malloc(info.buffer_size * sizeof(char*));
	info.sizes = malloc(sizeof(int) * info.buffer_size);
	info.freed = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
	info.filled = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
	info.lock = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	info.buff_count = 0;
    
    
	char requests[info.buffer_size][MAXLINE];	// incoming requests
	rio_t rio;
	
	pthread_t threads[thread_cnt];	// create worker threads
	int i;
	for(i = 0; i < thread_cnt; i++)
	{
		pthread_create(&threads[i], NULL, consume, &info);
	}

	listenfd = Open_listenfd(port);
	int size;
	for(i = 0; ; i = (i + 1) % info.buffer_size)	// round robin
	{
		// accept new connection
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA*)&clientaddr, (socklen_t*) &clientlen);

		// find file size, produce job
		Rio_readinitb(&rio, connfd);
		Rio_readlineb(&rio, requests[i], MAXLINE);
		size = getSize(requests[i]);
		produce(connfd, &info, requests[i], size);
	}
}

