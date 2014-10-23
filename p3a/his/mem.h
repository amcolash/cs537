#ifndef _MEM_H_
#define _MEM_H_

int Mem_Init(int size);

void* Mem_Alloc(int size);

int Mem_Free(void* ptr);

int Mem_Available();

void Mem_Dump();

#endif //_MEM_H_
