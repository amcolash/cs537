#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "udp.h"
#include "mfs.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 0;
  }

  char file[60];
  struct sockaddr_in addr;
  int port = atoi(argv[1]);

  strcpy(file, argv[2]);
  int socket = UDP_Open(port);

  UDP_FillSockAddr(&addr, "localhost", port);
  printf("Server running on port %d with image %s\n", port, argv[2]);

  if (socket < 0)
    return -1;

  char readbuffer[sizeof(message)];
  while (UDP_Read(socket, &addr, readbuffer, sizeof(readbuffer)) != -1) {
    printf("readbuffer %s\n", readbuffer);
  }

  return 0;
}
