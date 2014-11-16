#ifndef __REQUEST_H__

void requestError(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
int requestParseURI(char *uri, char *filename, char *cgiargs);
void requestGetFiletype(char *filename, char *filetype);
void requestServeDynamic(int fd, char *filename, char *cgiargs);
void requestServeStatic(int fd, char *filename, int filesize);
void requestHandle(int fd, char* buffer);

#endif
