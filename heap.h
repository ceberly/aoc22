#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef struct {
  void *item;
  unsigned int key; // for comparison, ie the "priority" or whatever is needed.
} heap_entry_t;

typedef struct {
  heap_entry_t **store;
  size_t capacity;
  size_t heap_size;
} heap_t;

heap_t new_heap(size_t capacity);
void heap_insert(heap_t *, heap_entry_t *);
heap_entry_t *heap_pop();

#endif
