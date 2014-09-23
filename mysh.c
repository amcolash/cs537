#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS 20

int countArg(char * buffer) {
  int count;
  int i;
  count = 1;
  for (i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == ' ') {
      count++;
    }
  }

  return count;
}

void parseCmd(char * buffer, char * args[]) {
  char * temp;
  int i;

  i = 0;
  temp = strtok(buffer," \n");

  while (temp != NULL && i < MAXARGS - 1) {
    printf("[%d]: %s\n", i, temp);
    args[i] = temp;
    temp = strtok(NULL, " \n");
    i++;
  }
  args[i] = NULL;
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];
  int argCount;
  int i;

  while (strcmp(buffer, "exit") != 0) {
    printf("mysh> ");
    fgets(buffer, 1024, stdin);
    argCount = countArg(buffer);
    char * args[argCount + 1];

    parseCmd(buffer, args);

    for(i = 0; i < argCount; i++) {
      printf("arg[%i]: %s\n", i, args[i]);
    }

    //char* arg[] = {"ls", "-l", NULL};
    execvp(args[0], args);


    if (strcmp(buffer, "test") == 0) {
      printf("something fancy!\n");
    } else {
      // something new
    }
  }

  exit(0);
}
