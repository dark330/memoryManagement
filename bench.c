/*
  Author: Yutong Xie
  UWNetID: yx99
  Date: May 22 2020
  FileName: bench.c

  This program executes a large number of calls to
  allocate and free blocks of memory in random order
*/
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"
int ntrials = 10000;
int pctget = 50;
int pctlarge = 10;
int small_limit = 200;
int large_limit = 20000;
int random_seed = 1;
int count = 0;
uintptr_t sizeSum = 0;
uintptr_t freeSizeSum = 0;
uintptr_t freeBlocksNum = 0;

/*
 * This function returns a randomly generated uintptr_t
 * that represents the size of a memory block to be allocated
*/
uintptr_t getSize() {
  int num = rand() % 100 + 1;
  if (num <= pctlarge) {  // large size
    return rand() % large_limit + small_limit;
  } else {
    return rand() % small_limit + 1;
  }
}

/*
 * This function returns a randomly
 * generated integer <= count
*/
int getIndex() {
  if (count <= 1) {
    return 0;
  }
  return rand() % count;
}

/*
 * This function rearranges the given array
*/
void rearrangeArray(int index, uintptr_t * blocks) {
  if (count <= 0) {
    count = 0;
    return;
  }
  if (count > 1) {
    if (index == count-1) {  // if element at the end freed
      blocks[index] = NULL;
    } else {
      blocks[index] = blocks[count-1];
    }
  } else {  // the last element in blocks was removed
    blocks[0] = NULL;
  }
  count--;
}

void printBlock(uintptr_t * blocks) {
  printf("[");
  for (int i = 0; i < count; i++) {
    if (blocks[i]) {
      printf("%d, ", i);
    }
  }
  printf("]\n");
}

/*
 * puts the given element(mem) to the appropriate location
 * of the given array(blocks)
*/
void putToArray(uintptr_t * blocks,  uintptr_t mem) {
  blocks[count] = mem;
  count++;
}

/*
 * Use the given clock and trial number(Integer i) to
 * print to stdout statistics about memory blocks
*/
void printStats(clock_t start, int i) {
    get_mem_stats(&sizeSum, &freeSizeSum, &freeBlocksNum);
    clock_t temp = clock() - start;
    printf("\n----------------------------------------\n");
    printf("Trial number: %d\n", i);
    printf("Total CPU time: %lu clicks (%f seconds)\n",
      temp, ((float)temp)/CLOCKS_PER_SEC);
    printf("Total storage acquired: %lu\n", sizeSum);
    printf("Free blocks: %lu\n", freeBlocksNum);
    uintptr_t avgSize = freeSizeSum / freeBlocksNum;
    printf("Free blocks average size: %lu\n", avgSize);
}

int main(int argc, char * argv[]) {
  random_seed = time(0);
  switch (argc) {
  case 7: random_seed = atoi(argv[6]);
  case 6: large_limit = atoi(argv[5]);
  case 5: small_limit = atoi(argv[4]);
  case 4: pctlarge = atoi(argv[3]);
  case 3: pctget = atoi(argv[2]);
  case 2: ntrials = atoi(argv[1]);
  default: {}
  }
  srand(random_seed);
  uintptr_t * blocks = (uintptr_t*)calloc(ntrials, sizeof(uintptr_t));
  clock_t t;
  t = clock();
  FILE * f = fopen("f1", "a");
  int printNum = (int)(ntrials / 10);
  if (printNum == 0) {
    printNum = 1;
  }
  for (int i = 0; i < ntrials; i++) {
    int num = rand() % 100 + 1;
    if (num <= pctget) {
      uintptr_t memSize = getSize();
      void* mem = getmem(memSize);
      if (mem) {
        int limit = 16;
        if (memSize < limit) {
          limit = memSize;
        }
        for (int i = 0; i < limit; i++) {
          void * start = (uintptr_t)mem + i;
          *(int *)start = 0xFE;
        }
        putToArray(blocks, mem);
      }
    } else {
      int index = getIndex();
      freemem((void*)blocks[index]);
      rearrangeArray(index, blocks);
    }
    print_heap(f);
    if (i > 0 && (i % printNum) == 0) {
      printStats(t, i);
    }
  }
  printStats(t, ntrials);
  free(blocks);
  fclose(f);
}


