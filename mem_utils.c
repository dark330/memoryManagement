/*
  Author: Yutong Xie, Ruikang Mao
  UWNetID: yx99, ruikang
  Date: May 22 2020
  FileName: mem_utils.c

  This program checks the free list data structure for 
  possible problems.
*/
#include <inttypes.h>
#include <assert.h>
#include "mem_impl.h"

Node* freeList;

/*
 * This function takes in a Node struct pointer and
 * returns a void* pointer to its corresponding
 * usable memory block. If the given Node struct
 * is NULL, this function returns NULL.
*/
void* toUsable(Node* mem) {
  if (!mem) {
    return NULL;
  }
  assert(mem->size > 0);
  uintptr_t curr = (uintptr_t) mem;
  curr += (uintptr_t)sizeof(Node);
  return (void*)curr;
}

/*
 * This function takes a pointer to a block
 * of usable memory, and returns a Node *
 * pointer to the corresponding Node struct
 * This function assumes the given parameter
 * is not NULL
*/
Node* toStruct(void* usable) {
  uintptr_t curr =  (uintptr_t) usable;
  curr -= sizeof(Node);
  return (Node*)curr;
}

/* Check for possible problems with the free list data structure.
 * If a problem is detected, the program is terminated
 * Otherwise, this function returns silently
*/
void check_heap() {
  if (freeList != NULL) {
    Node* curr = freeList->next;
    while (curr != NULL && curr->next != NULL) {
      // check if address is aligned properly
      assert((uintptr_t)curr % (uintptr_t)16 == 0);
      // check if blocks are ordered with strictly increasing memory addresses
      assert((uintptr_t) curr < (uintptr_t) curr->next);
      // check if block sizes are positive numbers and no smaller
      // than minimum size
      assert(curr->size > 0);
      assert(curr->size >= MIN_SIZE);
      // check if blocks overlap
      assert((uintptr_t) curr + curr->size + sizeof(Node) <
        (uintptr_t) curr->next);
      // check if blocks are not touching
      assert((uintptr_t) curr + curr->size + sizeof(Node) !=
        (uintptr_t) curr->next);
      curr = curr->next;
    }
  }
}


