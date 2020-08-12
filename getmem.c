/*
  Author: Ruikang Mao
  UWNetID: ruikang
  Date: May 22 2020
  FileName: getmem.c

  This file is part of CSE374 hw6. It contains implementation
  of function getmem that is responsible for memory allocation
*/
#include <inttypes.h>
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"

#define EXTRA_SIZE 100000

// Check if a proper block can be found in the free list
int isFound(uintptr_t size, Node* curr);

// Find the result
Node* getBlock(uintptr_t size, Node* curr);

// Get a good-sized block of storage from the underlying system
void newMem(uintptr_t size);

// Divide the block into two parts if the block is
// substantially larger than the storage requested
Node* split(uintptr_t size, Node* curr);

Node* freeList;
uintptr_t totalSize = 0;
uintptr_t totalFree = 0;
uintptr_t nFreeBlocks = 0;

/*
 * This function return a pointer to a new block
 * of storage with at least size bytes of memory
*/

void * getmem(uintptr_t size) {
  // Check at the beginning
  check_heap();
  // Check if the size is not positive
  if (size <= 0) {
    return NULL;
  }
  // For the first time, allocate memory for the empty list
  if (freeList == NULL) {
    freeList = (Node *)malloc(sizeof(Node) + EXTRA_SIZE);
    freeList->size = 0;
    freeList->next = NULL;
  }
  // Modify the size if needed
  if (size < MIN_SIZE) {
    size = MIN_SIZE;
  }
  if (size % 16 != 0) {
    size = size + (16 - size % 16);
  }

  // Check if there is a proper block and get a good-sized
  // block of storage from the underlying system if needed
  Node* curr = freeList;
  if (!isFound(size, curr)) {
    if (size > EXTRA_SIZE) {
      newMem(size);
    } else {
      newMem(EXTRA_SIZE);
    }
  }
  // Find a large enough block and split it if needed
  return toUsable(getBlock(size, curr));
}

int isFound(uintptr_t size, Node* curr) {
  while (curr->next != NULL) {
    if (curr->next->size >= size) {
      return 1;
    } else {
      curr = curr->next;
    }
  }
  return 0;
}

Node* getBlock(uintptr_t size, Node* curr) {
  while (curr->next != NULL) {
    if (curr->next->size >= size) {
      if (curr->next->size - size <= MIN_SIZE) {
        Node* block = curr->next;
        curr->next = curr->next->next;
        block->next = NULL;
        assert(block->size > 0);
        totalFree = totalFree - block->size - sizeof(Node);
        return block;
      } else if ((curr->next->size - size - sizeof(Node)) > 0) {
        return split(size, curr->next);
      }
    } else {
      curr = curr->next;
    }
  }
  return NULL;
}

void newMem(uintptr_t size) {
  Node* newBlock = (Node *)malloc(size + sizeof(Node));
  nFreeBlocks += 1;
  newBlock->size = size;
  newBlock->next = NULL;
  totalSize += size + sizeof(Node);
  totalFree += size + sizeof(Node);
  Node* curr = freeList;
  while (curr->next != NULL) {
    if ((uintptr_t)(curr->next) > (uintptr_t) newBlock) {
      newBlock->next = curr->next;
      curr->next = newBlock;
      return;
    } else {
      curr = curr->next;
    }
  }
  curr->next = newBlock;
  return;
}

Node* split(uintptr_t size, Node* curr) {
  if ((curr->size - size - sizeof(Node)) > 0) {
    Node* block = (Node *)((uintptr_t)curr + curr->size - size- sizeof(Node))+1;
  block->size = size;
  assert(block->size > 0);
  block->next = NULL;
  curr->size = curr->size - size - sizeof(Node);
  totalFree = totalFree - block->size - sizeof(Node);
  return block;
  }
  return NULL;
}


