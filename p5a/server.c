#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "udp.h"
#include "mfs.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 0;
  }

  struct sockaddr_in addr;
  int port = atoi(argv[1]);

  int socket = UDP_Open(port);
  UDP_FillSockAddr(&addr, "localhost", port);
  int fs = open(argv[2], O_CREAT | O_RDWR);

  if (socket < 0 || fs < 0)
    return -1;

  printf("Server running on port %d with image %s\n", port, argv[2]);

  char readbuffer[sizeof(message)];
  message *msg;

  while (UDP_Read(socket, &addr, readbuffer, sizeof(readbuffer)) != -1) {
    msg = (message*) readbuffer;
    response res;
    res.rc = 200;

    printf("readbuffer type %d\n", msg->type);

    if (msg->type == LOOKUP) {
      UDP_Write(socket, &addr,(char*) &res, sizeof(response));
    } else if (msg->type == SHUTDOWN) {
      fsync(fs);
      UDP_Write(socket, &addr,(char*) &res, sizeof(response));
      return 0;
    } else {
      printf("Invalid type\n");
    }

  }

  return 0;
}
