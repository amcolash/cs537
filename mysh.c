#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS 20

int parseCmd(char * buffer, char * args[]) {
  char * temp;
  int count;

  count = 0;
  temp = strtok(buffer," \n");

  while (temp != NULL && count < MAXARGS - 1) {
    printf("[%d]: %s\n",count, temp);
    args[count] = temp;
    temp = strtok(NULL, " \n");
    count++;
  }
  args[count] = NULL;

  return count;
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];
  char * args[MAXARGS];
  int argCount;

  while (strcmp(buffer, "exit") != 0) {
    printf("mysh> ");
    fgets(buffer, 1024, stdin);
    argCount = parseCmd(buffer, args);

    char* arg[] = {"ls", "-l", NULL};
    execvp(arg[0],arg);


    if (strcmp(buffer, "test") == 0) {
      printf("something fancy!\n");
    } else {
      // something new
    }

  }

  exit(0);
}
