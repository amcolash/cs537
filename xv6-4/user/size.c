/* check that address space size is updated in threads */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 0;
unsigned int size = 0;
int lock1, lock2;
int num_threads = 30;


#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int arg = 101;
   void *arg_ptr = &arg;
   
   lock(&lock1);
   lock(&lock2);

   int i;
   for (i = 0; i < num_threads; i++) {
      int thread_pid = thread_create(worker, arg_ptr);
      assert(thread_pid > 0);
   }

   size = (unsigned int)sbrk(0);
   printf(1, "parent: %d\n", size);

   while (global < num_threads) {
      unlock(&lock1);
      sleep(100);
      lock(&lock1);
   }

   global = 0;
   sbrk(10000);
   size = (unsigned int)sbrk(0);
   printf(1, "parent (after 10000): %d\n", size);
   unlock(&lock1);

   while (global < num_threads) {
      unlock(&lock2);
      sleep(100);
      lock(&lock2);
   }
   unlock(&lock2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   lock(&lock1);
   printf(1, "child: %d\n", (unsigned int)sbrk(0));
   assert((unsigned int)sbrk(0) == size);
   global++;
   unlock(&lock1);

   lock(&lock2);
   printf(1, "child (after 10000): %d\n", (unsigned int)sbrk(0));
   assert((unsigned int)sbrk(0) == size);
   global++;
   unlock(&lock2);

   exit();
}

