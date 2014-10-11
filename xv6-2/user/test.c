#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void listProc() {
  struct pstat stat;
  int i;

  if (getpinfo((char*) &stat) != -1) {
    printf(1, "PID\tInuse\tChosen\tTime\tCharge\n");
    //\tBid\tPercent\n");
    for (i=0; i < NPROC; i++) {
      if (stat.pid[i] != 0) {
        printf(1, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n", stat.pid[i], stat.inuse[i], stat.time[i], stat.chosen[i], stat.charge[i]);
        //stat.bid[i], stat.percent[i]);
      }
    }
  } else {
    printf(2, "Error getting pinfo\n");
  }

}

int main(int argc, char *argv[]) {
  //printf(1, "I am going to reserve %d\%\n", reserve(25));
  //printf(1, "Spot bid on for %d\n", spot(50));

  //spot(10);
  fork();
  reserve(75);

  fork();
  reserve(75);
  listProc();

  exit();
}
