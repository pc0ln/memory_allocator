#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAP 64000032

typedef struct Chunk_Data{
  size_t size;
  bool in_use;
  struct Chunk_Data* next;
  struct Chunk_Data* prev;
} Chunk_Data;

unsigned char heap[HEAP_CAP] = { 0 };
Chunk_Data *head_head = NULL;

void intializeHead() {
  //Creating metadata for initial heap
  head_head = (Chunk_Data *)heap;
  head_head->size = HEAP_CAP - sizeof(Chunk_Data);
  head_head->in_use = false;
  head_head->next = NULL;
  head_head->prev = NULL;
}

void *memAlloc(size_t size) {
  // Allocate chunk of size

  // cretes a current pointer to check chunks
  Chunk_Data *current = head_head;
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
    // Sets up header for other part of chunk
    next->size = (current->size - size - sizeof(Chunk_Data));
    next->in_use = false;
    next->prev = current;
    next->next = current->next;

    // Updates current metadata
    current->size = size;
    current->in_use = true;
    current->next = next;
  }
  return (void *)(current + 1);  
}

void memFree(void *ptr) {
  // Takes pointer and sets to not in use
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

void printChunks () {
  // Print chunks to get metadata
  Chunk_Data *current = head_head;
  while (current) {
    printf("Chunk at:%p size=%zu freed=%d\n", (void *)current, current->size, current->in_use);
    current = current->next;
  }
}

int main() {
  intializeHead();
  printf("Initial: ");
  printChunks();
  char *test_1 = memAlloc(32);
  char *test_2 = memAlloc(32);
  char *test_3 = memAlloc(32);
  char *test_4 = memAlloc(32);
  printf("\nallocated: \n");
  printChunks();
  printf("test_2: \n");
  memFree(test_2);
  printf("test_3: \n");
  memFree(test_3);
  char *test_5 = memAlloc(128);
  printf("test_1: \n");
  memFree(test_1);
  printChunks();
  printf("test_4: \n");
  memFree(test_4);
  memFree(test_5);
  printChunks();
  return 0;
}