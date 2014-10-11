#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC]; // whether this slot of the process process table is in use (1 or 0)
  int pid[NPROC];   // the PID of each process
  int chosen[NPROC]; // the number of times the process was chosen to run
  int time[NPROC]; // the number of ms the process has run
  int charge[NPROC]; // how much money (microdollars) the process has been charged

  // Extra info about process
  int percent[NPROC];
  int bid[NPROC];
};


#endif // _PSTAT_H_
