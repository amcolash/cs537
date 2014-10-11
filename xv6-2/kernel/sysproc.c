#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Reserve n-percentage of the CPU for a given process
int sys_reserve(void) {
  int n;
  if(argint(0, &n) < 0) {
    return -1;
  }
  else {
    if (n < 0 || n > 100) {
      cprintf("Error: Reservation not within 1-100\n");
      return -1;
    } else if (percentReserved + n > 200) {
      cprintf("Error: Reservation not allowed because not enough free CPU\n");
      return -1;
    } else {
      proc_reserve(n);
    }
  }

  return 0;
}

// Bid on computing time
int sys_spot(void) {
  int n;
  if(argint(0, &n) < 0) {
    return -1;
  } else {
    if (n < 1) {
      cprintf("Error: Must place a positive bid!\n");
      return -1;
    } else {
      proc_spot(n);
    }
  }

  return 0;
}

// Get info on all running processes
int sys_getpinfo(void) {
  char * ptr;
  struct pstat* stat;

  // Get pointer from syscall args, cast ptr to pstat
  argptr(0, &ptr, sizeof(struct pstat));
  stat = (struct pstat*) ptr;

  if (stat == NULL) {
    return -1;
  }

  // Fill pstat with information
  fill_pstat(stat);

  return 0;
}
