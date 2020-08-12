/*
  Author: Yutong Xie, Ruikang Mao
  UWNetID: yx99, ruikang
  Date: May 22 2020
  FileName: mem_impl.h

  This file contains functions and structures that are 
  shared between files
*/
#ifndef NODE_H
#define NODE_H
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_SIZE 32

/*
 * C structure of a memory block
*/
typedef struct Node {
  uintptr_t size;
  struct Node* next;
} Node;

extern Node* freeList;
extern uintptr_t totalSize;
extern uintptr_t totalFree;
extern uintptr_t nFreeBlocks;

/* Check for possible problems with the free list data structure.
 * If a problem is detected, the program is terminated
 * Otherwise, this function returns silently
*/
void check_heap();

/*
 * returns a void * pointer to the
 * usable memories of the given Node
*/
void* toUsable(Node* mem);


/*
 * returns a Node * pointer to the
 * Node struct of the given memory block
*/
Node* toStruct(void* usable);

#endif
