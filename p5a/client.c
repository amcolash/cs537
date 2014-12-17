#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mfs.h"
#include "udp.h"


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error, specify a port!\n");
    exit(1);
  }

  int client_port = atoi(argv[1]);
  printf("Attempting to connect to server on port %d\n", client_port);

  int socket =  MFS_Init("localhost", client_port);

  if (socket < 0) {
    printf("Uh-Oh! Couldn't connect to the server\n");
    exit(1);
  } else {
    printf("socket fd: %d\n", socket);
    MFS_Lookup(0, "testing");
    MFS_Shutdown();
  }

  exit(0);
}
