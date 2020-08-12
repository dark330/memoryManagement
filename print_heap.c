/*
  Author: Yutong Xie
  UWNetID: yx99
  Date: May 22 2020
  FileName: print_heap.c

  This program prints a formatted listing of blocks on the free list
*/
#include "mem.h"
#include "mem_impl.h"

Node * freeList;

/*
 * This function prints a formatted listing on given file f 
 * showing the blocks on the free list
*/
void print_heap(FILE * f) {
  Node * curr = freeList;
  fprintf(f,"\n---------------------\n");
  while(curr) {
    fprintf(f, "0x%x 0x%x\n", (uintptr_t)curr, (uintptr_t)curr->size);
    curr = curr->next;
  }
}
