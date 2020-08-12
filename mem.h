/*
  Author: Yutong Xie
  UWNetID: yx99
  Date: May 22 2020
  FileName: mem.h

  This is the header file of mem.c that declares functions
  to be shared between files
*/
#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


/*
 * Return a pointer to a new block of storage with at least
 * the given size bytes of memory
*/
void* getmem(uintptr_t size);


/*
 * Return the block of storage at the given location p to
 * the pool of available free storage
*/
void freemem(void* p);

/*
 * Store statistics about the current state of the memory
 * manager in the three integers
*/
void get_mem_stats(
  uintptr_t* total_size,
  uintptr_t* total_free,
  uintptr_t* n_free_blocks);

/*
 * Print a formatted listing on file f showing
 * the blocks on the free list.
*/
void print_heap(FILE * f);

#endif
