#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];

  while (strcmp(buffer, "exit") != 0) {
    printf("mysh> ");
    scanf("%s", buffer);
  }

  exit(0);
}
