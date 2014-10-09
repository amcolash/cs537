#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[]) {
  //printf(1, "I am going to reserve %d\%\n", reserve(25));
  //printf(1, "Spot bid on for %d\n", spot(50));
  //printf(1, "Here is some getpinfo output: %d\n", getpinfo());
  struct pstat *stat;
  int i;
  stat = NULL;

  getpinfo(stat);

  // Loop though the stat struct and output information about active processes
  for(i = 0; i < NPROC; i++) {
    // TODO
    // Without defining first, seems to be caching issues!?
    int inuse = stat->inuse[i];
    printf(1, "%d\n", inuse);
    if(stat->inuse[i] == 1) {
      printf(1, "--In P-Table, %d: here is process: %d (pid)--\n", i, stat->pid[i]);
    }
  }

  exit();
}
