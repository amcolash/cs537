#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"
#define check(exp, msg) if(exp) {} else {\
   printf(1, "%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit();}

int
spin() {
   while (1) {
      int i, j;
      for (i = 0; i < 10000000; i++) {
         j = i % 11;
      }
   }
}

int
main(int argc, char *argv[])
{
   int pids[3];
   int ppid = getpid();
   int r, i, j;

   pids[0] = fork();
   if (pids[0] == 0) {
      r = settickets(1);
      if (r != 0) {
         printf(1, "settickets failed");
         kill(ppid);
      }
      spin();
   }

   pids[1] = fork();
   if (pids[1] == 0) {
      r = settickets(2);
      if (r != 0) {
         printf(1, "settickets failed");
         kill(ppid);
      }
      spin();
   }

   pids[2] = fork();
   if (pids[2] == 0) {
      r = settickets(3);
      if (r != 0) {
         printf(1, "settickets failed");
         kill(ppid);
      }
      spin();
   }

   sleep(1500);

   int lticks[] = {-1, -1, -1};
   int hticks[] = {-1, -1, -1};
   struct pstat st;
   check(getpinfo(&st) == 0, "getpinfo");

   for(i = 0; i < NPROC; i++) {
      for(j = 0; j < 3; j++) {
         if (st.inuse[i] && st.pid[i] == pids[j]) {
            lticks[j] = st.lticks[i];
            hticks[j] = st.hticks[i];
         }
      }
   }

   for (i = 0; i < 3; i++) {
      kill(pids[i]);
      wait();
   }

   for (i = 0; i < 3; i++) {
      check(hticks[i] > 0 && lticks[i] > 0, "each process should have some hticks and lticks");
   }

   float ratio1 = (float)lticks[0] / (float)lticks[1];
   float ratio2 = (float)lticks[0] / (float)lticks[2];
   printf(1, "lticks child 1: %d\n", lticks[0]);
   printf(1, "lticks child 2: %d\n", lticks[1]);
   printf(1, "lticks child 3: %d\n", lticks[2]);
   check(ratio1 > .3 && ratio1 < .7, "child 1 to child 2 ratio should be about 1:2");
   check(ratio2 > .13 && ratio2 < .53, "child 1 to child 3 ratio should be about 1:3");

   printf(1, "TEST PASSED\n");
   exit();
}
