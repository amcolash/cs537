#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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

int hasChar(char * buffer, char search) {
  if (strchr(buffer, search) != NULL) {
    return 1;
  } else {
    return 0;
  }
}

int parseCmd(char * buffer, char * args[], int argCount) {
  char * temp;
  int i, special;

  // The special variable can have a range of values:
  // -2 -> Append file instead of outputting to stdout
  // -1 -> Create new file instead of outputting to stdout
  // 1 and greater -> Position of the pipe character in args array
  special = 0;
  i = 0;
  temp = strtok(buffer," \n");
  // Loop though the string, breaking at spaces or a newline
  // Look for "special" commands, and mark the special variable accordingly
  while (temp != NULL && i < MAXARGS - 1) {
    if (strcmp(temp, ">") == 0 && i == (argCount - 2)) {
      special = -1;
    } else if (strcmp(temp, ">>") == 0 && i == (argCount - 2)) {
      special = -2;
    } else if (strcmp(temp, "|") == 0) {
      special = i;
    }

    //printf("%s, special: %d\n", temp, special);
    // Create the args array from the given input string, splitting at spaces and newlines
    args[i] = temp;
    temp = strtok(NULL, " \n");
    i++;
  }

  args[i] = NULL;
  return special;
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  char buffer [1024];
  int argCount, outFile, status, special;
  int pipeFd[2];
  pid_t pid;

  // Loop forever, exit case below
  while (1) {
    printf("mysh> ");
    // Get user input
    fgets(buffer, 1024, stdin);
    // Count number of arguments in input (number of spaces)
    argCount = countArg(buffer);
    // Make an array, 1 item larger than the number of args - holds NULL for execvp
    char * args[argCount + 1];
    //printf("hasChar('>'): %d\n", hasChar(buffer, '>'));
    special = parseCmd(buffer, args, argCount);


    // Only continue if not a blank input
    if (strcmp(buffer, "\n") != 0) {
      // Exit if necessary
      if (strcmp(args[0], "exit") == 0) {
        exit(0);
      // Print working directory
      } else if (strcmp(args[0], "pwd") == 0) {
        printf("%s\n", getcwd(buffer, 1024));
      // Change working directory, possibly moving to $HOME
      } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
          chdir(getenv("HOME"));
        } else {
          chdir(args[1]);
        }
      } else {

        // Fork the process
        pid = fork();

        //printf("This line is from pid %d\n", pid);
        if (pid == 0) {

          char * args1[special + 1];
          char * args2[argCount - special];
          int i;

          // Set up args for execvp (if piped)
          args1[special] = NULL;
          args[argCount - special] = NULL;

          printf("special: %d\n", special);

          // If going to redirect output to a file
          if (special == -1 || special == -2) {
            printf("Using file: %s\n", args[argCount - 1]);

            // Create new file
            if (special == -1) {
              outFile = open(args[argCount - 1], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
            // Appending output file
            } else {
              outFile = open(args[argCount - 1], O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
            }

            if (outFile < 0) {
              fprintf(stderr, "Error: Cannot open output file: %s\n", args[argCount - 1]);
              exit(1);
            }
            // Change output stream from std out to file
            if (dup2(outFile, 1) == -1) {
              printf("error! - dup2\n");
            }
            args[argCount - 1] = NULL;
            args[argCount - 2] = NULL;

          // Piping output to another file
          } else if (special > 0) {
            // Set up a pipe for output
            pipe(pipeFd);
            printf("Piping output\n");
            close(pipeFd[1]);

            for (i = 0; i < special; i++) {
              args1[i] = args[i];
            }

            for (i = 0; i < argCount - special; i++) {
              args2[i] = args[i + special + 1];
            }
/*
            for (i = 0; i < sizeof(args1)/sizeof(args1[0]); i++) {
              printf("args1[%d]: %s\n", i, args1[i]);
            }
            for (i = 0; i < sizeof(args1)/sizeof(args2[0]); i++) {
              printf("args2[%d]: %s\n", i, args2[i]);
            }
*/
            // ls -la | grep Makefile
            // 0   1  2  3      4
            //
            // argCount = 5, special = 2
            // args1[2], args2[2]
            // 3 = [special + 1], 3 = [argCount - special]

          }

          if (special < 1) {
            if (execvp(args[0], args) == -1) {
              fprintf(stderr, "Error!\n");
            }
          } else {
            printf("piping time!\n");
          }
          exit(1);
        } else { // Parent process
          if (special > 0) {
            close(pipeFd[1]);
          }

          wait(&status);
        }
      }
    }

  }
  close(outFile);
  exit(0);
}
