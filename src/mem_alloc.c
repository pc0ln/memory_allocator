#include "mem_alloc.h"
#include <string.h>

Chunk_Data *head_head = NULL;
unsigned char heap[HEAP_CAP] = {0};
//memset(heap, 0, HEAP_CAP);

//Creating metadata for initial "heap"
void intializeHead() {
  heap_head = (Chunk_Data *)heap;
  heap_head->size = HEAP_CAP - sizeof(Chunk_Data);
  heap_head->in_use = false;
  heap_head->next = NULL;
  heap_head->prev = NULL;
}

// Allocate chunk of size
void *memAlloc(size_t size) {
  // creates a current pointer to check chunks
  Chunk_Data *current = heap_head;

  // Looks for a chunk of big enough size and not in use
  while (current && (current->size < size || current->in_use == true)) {
    current = current->next;
  }

  // If no chunk was found
  if (!current) {
    return NULL;
  }

  // Split current chunk if too big
  if (current->size > size + sizeof(Chunk_Data) + 1) { // Plus 1 too make sure the next chunk has at least one byte
    Chunk_Data *next = (Chunk_Data *)((unsigned char *)current + size + sizeof(Chunk_Data));
    // Sets up metadata for latter part of chunk
    next->size = (current->size - size - sizeof(Chunk_Data));
    next->in_use = false;
    next->prev = current;
    next->next = current->next;

    // Updates current metadata
    current->size = size;
    current->in_use = true;
    current->next = next;
  }
  // Returns pointer to memory root
  return (void *)(current + 1);  
}

// Takes pointer and sets chunk to free
void memFree(void *ptr) {
  // Shifts pointer to look at meta data
  Chunk_Data *chunk = (Chunk_Data *)ptr - 1;
  chunk->in_use = false;

  // Coalesce free chunks
  int total_size = chunk->size;
  Chunk_Data *test = chunk;

  // Check next chunks
  test = chunk->next;
  while (test && test->in_use == false) {
    total_size += (test->size + sizeof(Chunk_Data));
    test = test->next; 
  }
  Chunk_Data* next = test;

  // Check previous chunks
  test = chunk;
  while (test->prev && test->prev->in_use == false) {
    total_size += (test->prev->size + sizeof(Chunk_Data));
    test = test->prev;
  }
  test->size = total_size;
  test->next = next;
  if (next) {
    next->prev = test;
  }
}

// Print chunks to get metadata
void printChunks () {
  // Loops through list of chunks (linked list)
  Chunk_Data *current = heap_head;
  while (current) {
    printf("Chunk at:%p size=%zu freed=%d\n", (void *)current, current->size, current->in_use);
    current = current->next;
  }
}