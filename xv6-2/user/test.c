#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[]) {
  //printf(1, "I am going to reserve %d\%\n", reserve(25));
  //printf(1, "Spot bid on for %d\n", spot(50));

  struct pstat stat;
  int i;

  getpinfo((char*) &stat);

  for (i=0; i < 2; i++) {
    printf(1, "Pointer: %d\n", stat.pid[i]);
  }

  // Loop though the stat struct and output information about active processes
  //for(i = 0; i < NPROC; i++) {
    // Without defining first, seems to be caching issues!?

    //int inuse = stat->inuse[i];
    //printf(1, "%d\n", inuse);
    //if(stat->inuse[i] == 1) {
      //printf(1, "--In P-Table, %d: here is process: %d (pid)--\n", i, stat->pid[i]);
    //}
  //}

  exit();
}
