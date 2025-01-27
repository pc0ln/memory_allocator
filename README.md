# Minimalist Memory Allocator

Memory allocator made in C to practice how the memory allocation works.

## Description

To practice and understand how a memory allocator works, I made my own! I practiced handeling fragmentation, keeping track of the different chunks of memory, and which chunks to allocate. I made metadata structs at the beginning of each allocated chunk to keep track of previous chunk, next chunk, if free, and size of memory. I used the pointers to treat the different chunks like a linked list, which made it simplier to handle fragmentation. I used a First-Fit allocation algorithm to run through the linked list of chunks to find the first available memory chunk big enough, and then split up the chunk. The memory allocator using coalesence to handle fragmentation by checking when a chunk is free to see if the previous and next chunks are free, and if so adding the additional memory to the most "previous" chunk.

## Usage

To use this memory allocator, you need to clone the files and then include the header file.

```c
#include "mem_alloc.h"
```

Before allocating any memory, the head metadata must be initailized by running initializeHead();

```c
intializeHead();

// Allocated memory with memAlloc(numBytes)
char *test_1 = memAlloc(32);

// Print the current heap status with chunks to check fragmentation
printChunks();

// Use memFree(memoryPointer) to set the allocated chunk to free 
memFree(test_1);
```

## License 

[MIT](https://choosealicense.com/licenses/mit/)