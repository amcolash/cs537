#include "mfs.h"
#include "udp.h"

int socket_addr;
struct sockaddr_in socket_in;

int MFS_Init(char *hostname, int port) {
  socket_addr = socket(AF_INET, SOCK_DGRAM, 0);
  UDP_FillSockAddr(&socket_in, hostname, port);
  return socket_addr;
}

int MFS_Lookup(int pinum, char *name) {
  UDP_Write(socket_addr, &socket_in, "test", sizeof(message));
  return 0;
}

int MFS_Stat(int inum, MFS_Stat_t *m) {
  return 0;
}

int MFS_Write(int inum, char *buffer, int block) {
  return 0;
}

int MFS_Read(int inum, char *buffer, int block) {
  return 0;
}

int MFS_Creat(int pinum, int type, char *name) {
  return 0;
}

int MFS_Unlink(int pinum, char *name) {
  return 0;
}

int MFS_Shutdown() {
  return 0;
}
