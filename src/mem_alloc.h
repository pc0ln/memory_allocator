#ifndef MEM_ALLOC
#define MEM_ALLOC

#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAP 64000032

typedef struct Chunk_Data{
  size_t size;
  bool in_use;
  struct Chunk_Data* next;
  struct Chunk_Data* prev;
} Chunk_Data;

void intializeHead();
void *memAlloc(size_t size);
void memFree(void *ptr);
void printChunks();
extern Chunk_Data *head_head;

#endif