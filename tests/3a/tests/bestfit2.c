/* use best fit free space for allocation */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void *ptr[4];
   void *first, *best, *worst;

   assert(Mem_Alloc(8) != NULL);
   ptr[0] = Mem_Alloc(40);
   assert(Mem_Alloc(8) != NULL);
   ptr[1] = Mem_Alloc(56);
   assert(Mem_Alloc(8) != NULL);
   first = Mem_Alloc(256);
   assert(Mem_Alloc(8) != NULL);
   best = Mem_Alloc(128);
   assert(Mem_Alloc(8) != NULL);
   ptr[2] = Mem_Alloc(32);
   assert(Mem_Alloc(8) != NULL);
   worst = Mem_Alloc(512);
   assert(Mem_Alloc(8) != NULL);
   ptr[3] = Mem_Alloc(32);

   while(Mem_Alloc(128) != NULL);
   assert(m_error == E_NO_SPACE);

   assert(Mem_Free(ptr[2]) == 0);
   assert(Mem_Free(ptr[3]) == 0);
   assert(Mem_Free(first) == 0);
   assert(Mem_Free(best) == 0);
   assert(Mem_Free(ptr[1]) == 0);
   assert(Mem_Free(worst) == 0);
   assert(Mem_Free(ptr[0]) == 0);

   assert(Mem_Alloc(128) == best);

   exit(0);
}
