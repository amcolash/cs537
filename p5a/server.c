#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "udp.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 0;
  }

  char file[60];
  int port = atoi(argv[1]);
  strcpy(file, argv[2]);

  printf("Server running on port %d with image %s\n", port, argv[2]);
  int socket = UDP_Open(port);
  while (socket > 0) {
    printf("socket %d\n", socket);
  }

  return 0;
}
