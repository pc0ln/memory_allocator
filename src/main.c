#include "mem_alloc.h"

int main() {
  // Must Initalize head first
  intializeHead();
  // Allocated memory with memAlloc(numBytes)
  char *test_1 = memAlloc(32);
  // Print the current heap status with chunks to check fragmentation
  printChunks();
  // Use memFree(memoryPointer) to set the allocated chunk to free 
  memFree(test_1);
  return 0;
}