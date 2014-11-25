#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE (4096)

//int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;

int main(int argc, char *argv[]) {
  void *stack = malloc(PGSIZE);

  int tid = clone(stack);
  printf(1, "tid: %d\n", tid);

  exit();
}

/*
int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;
int count = 0;
int main(int argc, char *argv[]) {
  // int tid = fork();
  int tid = clone(stack);
  //printf(1, "Stack is at %p, tid: %d\n", stack, tid);

  if (tid < 0) {
    printf(2, "error!\n");
  } else if (tid == 0) {
    printf(1, "Child thread (%d) start, x: %d\n", count, x);
    count++;
    // child
    for(;;) {
      x++;
      //printf(1, "Child thread increment, x: %d\n", x);
      sleep(100);
    }
    printf(1, "Child thread done\n");
  } else {
    printf(1, "Parent thread\n");
    // parent
    for(;;) {
      printf(1, "x = %d\n", x);
      sleep(100);
    }
    printf(1, "Parent thread done\n");
  }

  exit();
}*/
