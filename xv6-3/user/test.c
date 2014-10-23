#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  printf(1, "Attempting to make a stack overflow!\n");
  int overflow[99999999];
  overflow[1] = 0;

  char * i;
  i = NULL;
  *i = 'a';
  printf(1, "Should not be here!\n");
  exit();
}
