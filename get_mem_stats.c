/*
  Author: Ruikang Mao
  UWNetID: ruikang
  Date: May 22 2020
  FileName: get_mem_stats.c

  This file is part of CSE374 hw6. It contains implementation
  of function get_mem_stats that stores statistics about the
  current state of the memory manager in the given pointers
*/
#include "mem.h"
#include "mem_impl.h"

/*
 * This function stores statistics about the
 * current state of the memory manager
 * in the given pointers.
*/
void get_mem_stats(
  uintptr_t* total_size,
  uintptr_t* total_free,
  uintptr_t* n_free_blocks) {
  *total_size = totalSize;
  *total_free = totalFree;
  *n_free_blocks = nFreeBlocks;
}

