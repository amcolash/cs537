#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {

  char* name = "a";
  //char* name = "tmp/a";
  //mkdir("tmp");

  int file = open(name, O_CREATE | O_MIRRORED);
  close(file);

  unlink(name);

  exit();
}
