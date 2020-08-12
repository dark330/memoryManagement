/*
  Author: Yutong Xie
  UWNetID: yx99
  Date: May 22 2020
  FileName: freemem.c

  This file is part of CSE374 hw6. It contains implementation
  of function freemem that return the block of storage at
  location p to the pool of available free storage
*/
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

Node* combine(Node* target);

Node* findFront(Node* target);

void freemem(void* p1);

Node* freeList;

/*
 * return the block of storage at location p1 to
 * the pool of available free storage
*/
void freemem(void * p1) {
  if (!p1) {
    return;
  }
  Node* p = toStruct(p1);
  check_heap();
  Node* front = findFront(p);
  p->next = front->next;
  front->next = p;
  Node* curr = freeList->next;
  totalFree = totalFree + p->size + sizeof(Node);
  nFreeBlocks++;
  while (curr) {
    curr = combine(curr);
    curr = curr->next;
  }
}

/*
 * returns a Node * pointer to a Node
 * in the freelist to which the given node
 * should be appended
*/
Node* findFront(Node* target) {
  Node* curr = freeList;
  // find the node before target
  while (curr->next != NULL && curr->next <= target) {
    curr = curr->next;
  }
  return curr;
}

/*
 * Combine the Nodes that are physically
 * adjacent to the given Node.
*/
Node* combine(Node * target) {
  if (!target->next) {
    return target;
  }
  uintptr_t next = (uintptr_t) target->next;
  uintptr_t curr = (uintptr_t) target;
  uintptr_t calculated = curr + sizeof(Node) + target->size;
  if (calculated == next) {
    target->size = target->size + target->next->size + sizeof(Node);
    target->next = target->next->next;
    nFreeBlocks--;
    return combine(target);
  }
  return target;
}


