#include "mfs.h"
#include "udp.h"

int socket_addr;
struct sockaddr_in socket_in;

int MFS_Init(char *hostname, int port) {
  socket_addr = socket(AF_INET, SOCK_DGRAM, 0);
  UDP_FillSockAddr(&socket_in, hostname, port);
  return 0;
}

int MFS_Lookup(int pinum, char *name) {

  message msg;
  msg.type = LOOKUP;
  UDP_Write(socket_addr, &socket_in, (char*) &msg, sizeof(message));

  response res;
  UDP_Read(socket_addr, &socket_in, (char*) &res, sizeof(response));
  printf("Client rc %d\n", res.rc);

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
  message msg;
  response res;
  msg.type = SHUTDOWN;
  UDP_Write(socket_addr, &socket_in, (char*) &msg, sizeof(message));
  UDP_Read(socket_addr, &socket_in, (char*) &res, sizeof(response));
  return 0;
}
