#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 20

int countArg(char * buffer) {
  int count, i;
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
    //printf("[%d]: %s\n", i, temp);
    args[i] = temp;
    temp = strtok(NULL, " \n");
    i++;
  }
  args[i] = NULL;
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];
  int argCount, status;
  pid_t pid;

  while (1) {
    printf("mysh> ");
    fgets(buffer, 1024, stdin);
    argCount = countArg(buffer);
    char * args[argCount + 1];

    parseCmd(buffer, args);
    if (strcmp(buffer, "\n") != 0) {
      if (strcmp(args[0], "exit") == 0) {
        exit(0);
      } else if (strcmp(args[0], "pwd") == 0) {
        printf("%s\n", getcwd(buffer, 1024));
      } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
          chdir(getenv("HOME"));
        } else {
          chdir(args[1]);
        }
      } else if (strcmp(buffer, "\n") != 0) {
        pid = fork();
        //printf("This line is from pid %d\n", pid);
        if (pid == 0) {
          if (execvp(args[0], args) == -1) {
            fprintf(stderr, "Error!\n");
          }
          exit(1);
        } else {
          wait(&status);
        }
      }
    }

  }

  exit(0);
}
