#include <assert.h>

#include "heap.h"

int_heap_t new_int_heap(size_t capacity) {
  int *store = malloc(sizeof(int) * capacity);
  assert(store != NULL);

  int_heap_t r = {
    .store = store,
    .heap_size = 0,
    .capacity = capacity,
  };

  return r;
}
