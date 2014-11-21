#include "types.h"
#include "stat.h"
#include "user.h"

int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;

int main(int argc, char *argv[]) {
  printf(1, "Stack is at %p\n", stack);
  // int tid = fork();
  int tid = clone(stack);
  printf(1, "stack is cloned and back in test\n");
  printf(1, "tid: %d\n", tid);

  if (tid < 0) {
    printf(2, "error!\n");
  } else if (tid == 0) {
    // child
    printf(1, "got to child\n");
    for(;;) {
      x++;
      sleep(100);
    }
  } else {
    // parent
    printf(1, "got to parent\n");
    for(;;) {
      printf(1, "x = %d\n", x);
      sleep(100);
    }
  }

  exit();
}
