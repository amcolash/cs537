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
		printf("loop\n");
		// accept new connection
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA*)&clientaddr, (socklen_t*) &clientlen);

		// find file size, produce job
		Rio_readinitb(&rio, connfd);
		Rio_readlineb(&rio, requests[i], MAXLINE);
		size = getSize(requests[i]);
		produce(connfd, &info, requests[i], size);
		printf("~loop\n");
	}
}

