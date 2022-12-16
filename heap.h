#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef struct {
  int *store;
  size_t capacity;
  size_t heap_size;
} int_heap_t;

int_heap_t new_int_heap(size_t capacity);

#endif
