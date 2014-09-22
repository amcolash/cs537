#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parseCmd(char * buffer) {
  char * temp;
  int count;

  count = 0;
  temp = strtok(buffer," \n");

  while (temp != NULL) {
    printf("[%d]: %s\n",count, temp);
    temp = strtok(NULL, " \n");
    count++;
  }
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];

  while (strcmp(buffer, "exit") != 0) {
    printf("mysh> ");
    fgets(buffer, 1024, stdin);
    parseCmd(buffer);


    if (strcmp(buffer, "test") == 0) {
      printf("something fancy!\n");
    } else if (strcmp(buffer, "xxx") == 0) {
      // do something else
    } else {
      // something new
    }

  }

  exit(0);
}
