/******************************************************************************
 * FILENAME:     mem.c
 * AUTHOR:       cherin@cs.wisc.edu <Cherin Joseph>
 * DATE:         20 Nov 2013
 * PROVIDES:     Contains a set of library functions for memory allocation
 *
 * MODIFIED BY:  Andrew McOlash, Lecture 1
 * * *****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "mem.h"

/* this structure serves as the header for each block */
typedef struct block_hd{
  /* The blocks are maintained as a linked list */
  /* The blocks are ordered in the increasing order of addresses */
  struct block_hd* next;

  /* size of the block is always a multiple of 4 */
  /* ie, last two bits are always zero - can be used to store other information*/
  /* LSB = 0 => free block */
  /* LSB = 1 => allocated/busy block */

  /* For free block, block size = size_status */
  /* For an allocated block, block size = size_status - 1 */

  /* The size of the block stored here is not the real size of the block */
  /* the size stored here = (size of block) - (size of header) */
  int size_status;

}block_header;

/* Global variable - This will always point to the first block */
/* ie, the block with the lowest address */
block_header* list_head = NULL;

int Mem_Availible() {
  printf("Nothing here yet\n");
}

/* Function used to Initialize the memory allocator */
/* Not intended to be called more than once by a program */
/* Argument - sizeOfRegion: Specifies the size of the chunk which needs to be allocated */
/* Returns 0 on success and -1 on failure */
int Mem_Init(int sizeOfRegion)
{
  int pagesize;
  int padsize;
  int fd;
  int alloc_size;
  void* space_ptr;
  static int allocated_once = 0;

  if(0 != allocated_once)
  {
    fprintf(stderr,"Error:mem.c: Mem_Init has allocated space during a previous call\n");
    return -1;
  }
  if(sizeOfRegion <= 0)
  {
    fprintf(stderr,"Error:mem.c: Requested block size is not positive\n");
    return -1;
  }

  /* Get the pagesize */
  pagesize = getpagesize();

  /* Calculate padsize as the padding required to round up sizeOfRegio to a multiple of pagesize */
  padsize = sizeOfRegion % pagesize;
  padsize = (pagesize - padsize) % pagesize;

  alloc_size = sizeOfRegion + padsize;

  /* Using mmap to allocate memory */
  fd = open("/dev/zero", O_RDWR);
  if(-1 == fd)
  {
    fprintf(stderr,"Error:mem.c: Cannot open /dev/zero\n");
    return -1;
  }
  space_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (MAP_FAILED == space_ptr)
  {
    fprintf(stderr,"Error:mem.c: mmap cannot allocate space\n");
    allocated_once = 0;
    return -1;
  }

  allocated_once = 1;

  /* To begin with, there is only one big, free block */
  list_head = (block_header*)space_ptr;
  list_head->next = NULL;
  /* Remember that the 'size' stored in block size excludes the space for the header */
  list_head->size_status = alloc_size - (int)sizeof(block_header);

  return 0;
}


/* Function for allocating 'size' bytes. */
/* Returns address of allocated block on success */
/* Returns NULL on failure */
/* Here is what this function should accomplish */
/* - Check for sanity of size - Return NULL when appropriate */
/* - Round up size to a multiple of 4 */
/* - Traverse the list of blocks and allocate the first free block which can accommodate the requested size */
/* -- Also, when allocating a block - split it into two blocks when possible */
/* Tips: Be careful with pointer arithmetic */
void* Mem_Alloc(int size)
{

  int block_size;
  int rounded_size;
  int total_size;

  /* Round the requested size to the nearest 4-byte size */
  block_size = (int) sizeof(block_header);
  rounded_size = size;
  while (rounded_size % 4 != 0) {
    rounded_size++;
  }
  /* Calculate total size taken up */
  total_size = rounded_size + block_size;

  block_header* pointer;
  pointer = list_head;

  int done;
  done = 0;

  /* Traverse block list looking for a free space */
  if (pointer->size_status >= rounded_size && pointer->size_status % 4 == 0) {
    done = 1;
  } else if (pointer->next == NULL) {
    pointer = NULL;
    done = -1;
  } else {
    while (done == 0) {
      pointer = pointer->next;
      if (pointer == NULL) {
        done = -1;
      } else if (pointer->size_status >= rounded_size && pointer->size_status % 4 == 0) {
        done = 1;
      }
    }
  }


  if (pointer != NULL && pointer->size_status >= rounded_size && done != -1) {
    int new_size;

    /* Calculate the new size of next block */
    new_size = pointer->size_status - total_size;

    /* Check if block able to be used */
    if (pointer->size_status >= rounded_size) {
      if (pointer->size_status == rounded_size) {
        /* Set size_status to data size + 1 (Used block) */
        pointer->size_status = rounded_size + 1;
      } else if (pointer->size_status <= total_size + block_size) {
        /* This case will use an entire block if not able to split it*/
        /* ie if free block is 20 bytes, and allocated 12 of those bytes */
        /* Use all 20 bytes because not able to allocate 8 bytes for new block */

        /* Set size_status to data size + 1 (Used block) */
        pointer->size_status = pointer->size_status + 1;
      } else {
        /* Split a block into two blocks */
        block_header * temp;
        temp = pointer->next;
        pointer->next = (block_header *) (((char *) pointer) + total_size);
        pointer->next->next = temp;

        /* Set size_status to data size + 1 (Used block) */
        pointer->size_status = rounded_size + 1;
        pointer->next->size_status = new_size;
      }
    } else {
      printf("*** ERROR: Unable to allocate, not enough free space ***\n");
      return NULL;
    }

    /* Return the pointer to the allocated block */
    return ((char *)pointer) + block_size;

  } else {
    printf("*** ERROR: Unable to allocate, not enough space ***\n");
    return NULL;
  }

}

/* Function for freeing up a previously allocated block */
/* Argument - ptr: Address of the block to be freed up */
/* Returns 0 on success */
/* Returns -1 on failure */
/* Here is what this function should accomplish */
/* - Return -1 if ptr is NULL */
/* - Return -1 if ptr is not pointing to the first byte of a busy block */
/* - Mark the block as free */
/* - Coalesce if one or both of the immediate neighbours are free */
int Mem_Free(void *ptr)
{

  /* Check if the pointer is valid or NULL */
  if (ptr == NULL) {
    printf("*** ERROR: Cannot free NULL pointer ***\n");
    return -1;
  }


  int block_size;
  block_size = (int)sizeof(block_header);
  ptr = ((char *) ptr) - block_size;


  block_header * prev;
  block_header * curr;
  block_header * next;
  int found;

  prev = curr = list_head;
  found = 0;

  /* Look through the list of blocks for the given block */
  while (curr->next != NULL && found == 0) {
    if (ptr == curr) {
      found = 1;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  /* If found block (could be an error) is not the same as requested, error*/
  if (curr != ptr) {
    printf("*** ERROR: Bad pointer ***\n");
    return -1;
  }


  /* Check if the given block is free, if it is, error*/
  if (curr->size_status % 4 != 0) {
    curr->size_status = curr->size_status - 1;
  } else {
    printf("*** ERROR: Block already free ***\n");
    return -1;
  }

  /* Coalesce the previous and current blocks if possible*/
  if (prev->size_status % 4 == 0 && (block_header *) (((char *) prev) + prev->size_status + block_size) == curr) {
    prev->next = curr->next;
    prev->size_status = prev->size_status + curr->size_status + block_size;
    curr = prev;
  }

  /* Coalesce the current and next blocks if possible */
  if (curr->next != NULL) {
    next = curr->next;
    if (next->size_status % 4 == 0 && (block_header *) (((char *) curr) + curr->size_status + block_size) == next) {
      curr->next = next->next;
      curr->size_status = curr->size_status + next->size_status + block_size;
    }
  }

  /* If the function got here, return valid free operation */
  return 0;
}

/* Function to be used for debug */
/* Prints out a list of all the blocks along with the following information for each block */
/* No.      : Serial number of the block */
/* Status   : free/busy */
/* Begin    : Address of the first useful byte in the block */
/* End      : Address of the last byte in the block */
/* Size     : Size of the block (excluding the header) */
/* t_Size   : Size of the block (including the header) */
/* t_Begin  : Address of the first byte in the block (this is where the header starts) */
void Mem_Dump()
{
  int counter;
  block_header* current = NULL;
  char* t_Begin = NULL;
  char* Begin = NULL;
  int Size;
  int t_Size;
  char* End = NULL;
  int free_size;
  int busy_size;
  int total_size;
  char status[5];

  free_size = 0;
  busy_size = 0;
  total_size = 0;
  current = list_head;
  counter = 1;
  fprintf(stdout,"************************************Block list***********************************\n");
  fprintf(stdout,"No.\tStatus\tBegin\t\tEnd\t\tSize\tt_Size\tt_Begin\n");
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  while(NULL != current)
  {
    t_Begin = (char*)current;
    Begin = t_Begin + (int)sizeof(block_header);
    Size = current->size_status;
    strcpy(status,"Free");
    if(Size & 1) /*LSB = 1 => busy block*/
    {
      strcpy(status,"Busy");
      Size = Size - 1; /*Minus one for ignoring status in busy block*/
      t_Size = Size + (int)sizeof(block_header);
      busy_size = busy_size + t_Size;
    }
    else
    {
      t_Size = Size + (int)sizeof(block_header);
      free_size = free_size + t_Size;
    }
    End = Begin + Size;
    fprintf(stdout,"%d\t%s\t0x%08lx\t0x%08lx\t%d\t%d\t0x%08lx\n",counter,status,(unsigned long int)Begin,(unsigned long int)End,Size,t_Size,(unsigned long int)t_Begin);
    total_size = total_size + t_Size;
    current = current->next;
    counter = counter + 1;
  }
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  fprintf(stdout,"*********************************************************************************\n");

  fprintf(stdout,"Total busy size = %d\n",busy_size);
  fprintf(stdout,"Total free size = %d\n",free_size);
  fprintf(stdout,"Total size = %d\n",busy_size+free_size);
  fprintf(stdout,"*********************************************************************************\n");
  fflush(stdout);
  return;
}
