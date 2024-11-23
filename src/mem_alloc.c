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
Chunk_Data *head = NULL;

void intializeHead() {
  //Creating metadata for initial heap
  head = (Chunk_Data *)heap;
  head->size = HEAP_CAP - sizeof(Chunk_Data);
  head->in_use = false;
  head->next = NULL;
  head->prev = NULL;
}

void *memAlloc(size_t size) {
  // Allocate chunk of size

  // cretes a current pointer to check chunks
  Chunk_Data *current = head;
  // Looks for a chunk of big enough size and not in use
  while (current && (current->size < size || current->in_use == true)) {
    current = current->next;
  }

  // If no chunk was found
  if (current) {
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

  void *memory_root = (void *)(current + 1);  
  return memory_root;
}

void memFree(void *ptr) {
  // Takes pointer ands frees chunk
  Chunk_Data *chunk = (Chunk_Data *)ptr - 1;
  chunk->in_use = false;
  Chunk_Data *next = chunk->next;
  while (next->in_use == false) {
    chunk->size += next->size + sizeof(Chunk_Data);
  }
}

int main() {
  intializeHead();
  char *alpha = memAlloc(26);
  for (int i = 0; i<26; ++i) {
    alpha[i] = 'A' + i;
  }
  for (int i = 0; i<26; ++i) {
    printf("%c ", alpha[i]);
  }
  printf("%d \n", *(alpha - 8));
  return 0;
}