/* many odd sized allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   assert(Mem_Alloc(1) != NULL);
   assert(Mem_Alloc(5) != NULL);
   assert(Mem_Alloc(14) != NULL);
   assert(Mem_Alloc(8) != NULL);
   assert(Mem_Alloc(1) != NULL);
   assert(Mem_Alloc(4) != NULL);
   assert(Mem_Alloc(9) != NULL);
   assert(Mem_Alloc(33) != NULL);
   assert(Mem_Alloc(55) != NULL);
   exit(0);
}
