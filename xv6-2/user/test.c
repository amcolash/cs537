#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void listProc() {
  struct pstat stat;
  int i;

  if (getpinfo(&stat) != -1) {
//    printf("Total reserved: %d\n", percentReserved);
    printf(1, "PID\tInuse\tChosen\tTime\tCharge\tBid\tPercent\n");
    for (i=0; i < NPROC; i++) {
      if (stat.pid[i] != 0) {
        printf(1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n", stat.pid[i], stat.inuse[i], stat.chosen[i], stat.time[i], stat.charge[i], stat.bid[i], stat.percent[i]);
      }
    }
  } else {
    printf(2, "Error getting pinfo\n");
  }

}

int main(int argc, char *argv[]) {
  //printf(1, "I am going to reserve %d\%\n", reserve(25));
  //printf(1, "Spot bid on for %d\n", spot(50));

  /*
  int n, times;
  times = 2;

  for(n = 0; n < times; n++){
    if (fork() == 0) {
      reserve(10);
      reserve(20);
      exit();
    } else {
      reserve(20);
      wait();
    }
  }
  */
  int i;

  listProc();
  reserve(50);

  for (i = 0; i < 99999; i++) {}

  /*
  if (fork() == 0) {
    spot(25);
  } else {
    wait();
  }
  */

  listProc();
  exit();
}
