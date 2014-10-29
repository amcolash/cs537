/* stack should be at high end of address space */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define assert(x) if (x) {} else { \
  printf(1, "%s: %d ", __FILE__, __LINE__); \
  printf(1, "assert failed (%s)\n", # x); \
  printf(1, "TEST FAILED\n"); \
  exit(); \
}

int
main(int argc, char *argv[])
{
  int local;
  // no magic involved here. 0x9ffdc is where local should be after space for function arguments
  assert(&local == (void*) 0x9ffdc);
  printf(1, "TEST PASSED\n");
  exit();
}
