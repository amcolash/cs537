#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[]) {
  //printf(1, "I am going to reserve %d\%\n", reserve(25));
  //printf(1, "Spot bid on for %d\n", spot(50));
  //printf(1, "Here is some getpinfo output: %d\n", getpinfo());
  struct pstat *stat;
  stat = NULL;
  getpinfo(stat);

  printf(1, "Well crud, need to figure this out ASAP, my pointer is %d though!\n", stat);
  exit();
}
