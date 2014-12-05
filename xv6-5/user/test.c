#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  char* name = "abc.txt";

  int file = open(name, O_CREATE | O_MIRRORED);
  close(file);

  unlink(name);

  exit();
}
