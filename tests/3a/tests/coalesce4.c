/* check for coalesce free space (last chunk)*/
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

#define HEADER (16) // Assumes Headers will never be BIGGER than this
#define SLACK (32)

int main() {
   assert(Mem_Init(4096) == 0);
   void * ptr[4];

   ptr[0] = Mem_Alloc(880);
   assert(ptr[0] != NULL);

   ptr[1] = Mem_Alloc(880);
   assert(ptr[1] != NULL);

   ptr[2] = Mem_Alloc(880);
   assert(ptr[2] != NULL);

   ptr[3] = Mem_Alloc(880);
   assert(ptr[3] != NULL);

   assert(Mem_Alloc(880) == NULL);
   assert(m_error == E_NO_SPACE);
   // last free chunk is not this big
   int free = (4096 - (880 + HEADER) * 4) - SLACK; // Minimally this much

   assert(Mem_Free(ptr[3]) == 0);
   free += 880;

   ptr[2] = Mem_Alloc(free);
   assert(ptr[2] != NULL);

   exit(0);
}
