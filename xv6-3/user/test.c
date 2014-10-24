#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  printf(1, "Attempting to make a stack overflow!\n");
  int overflow[9999];
  overflow[0] = 0;

  if (overflow[0] == 0) {
    printf(1, "Yay, we didn't crash :)\n");
  }

  char * i;
  i = NULL;
  *i = 'a';
  printf(1, "Should not be here!\n");
  exit();
}
