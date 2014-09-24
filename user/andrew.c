#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
  printf(1, "addnum(0): %d\n", addnum(0));
  printf(1, "addnum(1): %d\n", addnum(1));
  printf(1, "addnum(5): %d\n", addnum(5));
  printf(1, "addnum(10): %d\n", addnum(10));
  exit();
}
