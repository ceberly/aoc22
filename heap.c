#include <assert.h>

#include "heap.h"

heap_t new_heap(size_t capacity) {
  heap_entry_t **store = malloc(sizeof(heap_entry_t *) * capacity);
  assert(store != NULL);

  heap_t r = {
      .store = store,
      .heap_size = 0,
      .capacity = capacity,
  };

  return r;
}

static inline size_t heap_parent(size_t index) { return index >> 1; }

static inline size_t heap_left_child(size_t index) { return index << 1; }

static inline size_t heap_right_child(size_t index) {
  return heap_left_child(index) + 1;
}

static void heap_heapify(heap_t *heap, size_t index) {
  assert(heap != NULL);
  assert(heap->store != NULL);
  assert(index > 0);

  size_t left = heap_left_child(index);
  size_t right = heap_right_child(index);
  size_t largest;

  if (left <= heap->heap_size &&
      heap->store[left - 1]->key > heap->store[index - 1]->key) {
    largest = left;
  } else {
    largest = index;
  }

  if (right <= heap->heap_size &&
      heap->store[right - 1]->key > heap->store[largest - 1]->key) {
    largest = right;
  }

  if (largest != index) {
    heap_entry_t *tmp = heap->store[index - 1];
    heap->store[index - 1] = heap->store[largest - 1];
    heap->store[largest - 1] = tmp;

    heap_heapify(heap, largest);
  }
}

void heap_insert(heap_t *heap, heap_entry_t *entry) {
  assert(heap != NULL);
  assert(heap->store != NULL);
  assert(heap->heap_size < heap->capacity);
  assert(entry != NULL);

  heap->heap_size++;
  size_t index = heap->heap_size;

  while (index > 1 && heap->store[heap_parent(index) - 1]->key < entry->key) {
    heap->store[index - 1] = heap->store[heap_parent(index) - 1];
    index = heap_parent(index);
  }

  heap->store[index - 1] = entry;
}

heap_entry_t *heap_pop(heap_t *heap) {
  assert(heap != NULL);
  assert(heap->store != NULL);
  assert(heap->heap_size > 0);

  heap_entry_t *max = heap->store[0];
  heap->store[0] = heap->store[heap->heap_size - 1];
  heap->heap_size--;

  heap_heapify(heap, 1);

  return max;
}

#ifdef TEST
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define K 10000

int main(void) {
  srand(time(NULL));

  heap_entry_t pool[K];
  heap_entry_t inserted[K];

  heap_t H = new_heap(K);
  for (size_t i = 0; i < K; i++) {
    int v = rand();

    // don't care about the item, only the key...
    pool[i].key = v;
    heap_insert(&H, &(pool[i]));

    // check heap property
    for (size_t j = 2; j <= H.heap_size; j++) {
      if (H.store[heap_parent(j) - 1]->key < H.store[j - 1]->key) {
        fprintf(stderr, "heap property failed at index: %zu, %d < %d\n", j,
                H.store[heap_parent(j) - 1]->key, H.store[j - 1]->key);
        return EXIT_FAILURE;
      }
    }

    inserted[i] = pool[i];
  }

  // check pop in sorted order
  heap_entry_t tmp[K];
  heap_entry_t *p = heap_pop(&H);
  tmp[0] = *p;

  for (size_t i = 1; i < K; i++) {
    heap_entry_t *p = heap_pop(&H);

    for (size_t j = 0; j < i - 1; j++) {
      if (p->key > tmp[j].key) {
        fprintf(stderr, "popped element in wrong order: %d < %d\n", p->key,
                tmp[j].key);
        return EXIT_FAILURE;
      }
    }

    tmp[i] = *p;
  }

  // check all inserted elements were popped out
  for (size_t i = 0; i < K; i++) {
    bool found = false;
    for (size_t j = 0; j < K; j++) {
      if (inserted[i].key == tmp[j].key) {
        found = true;
        break;
      }
    }

    if (found) continue;

    fprintf(stderr,
            "inserted element at index %zu (%d) not found in popped elements\n",
            i, inserted[i].key);
    return EXIT_FAILURE;
  }

  printf("OK\n");

  return EXIT_SUCCESS;
}
#endif
