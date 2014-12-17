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
  if (strlen(name) > 60) {
    return -1;
  }

  message msg;
  msg.type = LOOKUP;
  msg.inum = pinum;
  msg.cmd[0] = LOOKUP;
  strcpy(msg.name, name);
  UDP_Write(socket_addr, &socket_in, (char*) &msg, sizeof(message));

  response res;
  UDP_Read(socket_addr, &socket_in, (char*) &res, sizeof(response));

  return res.rc;
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
  if (strlen(name) > 60) {
    return -1;
  }

  message msg;
  msg.type = LOOKUP;
  msg.inum = pinum;
  msg.cmd[0] = CREAT;
  strcpy(msg.name, name);
  UDP_Write(socket_addr, &socket_in, (char*) &msg, sizeof(message));

  response res;
  UDP_Read(socket_addr, &socket_in, (char*) &res, sizeof(response));

  return res.rc;
}

int MFS_Unlink(int pinum, char *name) {
  if (strlen(name) > 60) {
    return -1;
  }
  return 0;
}

int MFS_Shutdown() {
  message msg;
  response res;
  msg.cmd[0] = SHUTDOWN;
  UDP_Write(socket_addr, &socket_in, (char*) &msg, sizeof(message));
  UDP_Read(socket_addr, &socket_in, (char*) &res, sizeof(response));
  return 0;
}
