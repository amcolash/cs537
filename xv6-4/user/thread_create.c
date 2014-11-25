#include "types.h"
#include "user.h"

int thread_create(void (*fn) (void *), void *arg) {
  void *stack = malloc(4096);
  int tid = clone(stack);

  if (tid == 0) {
    (*fn) (arg);
    free(stack);
    exit();

  } else {
    return tid;
  }

}
