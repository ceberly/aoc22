#ifndef AOC_H
#define AOC_H

#include <stdlib.h>

typedef struct {
  size_t len;
  char *buf;
} char_buf_t;

char_buf_t memory_map_file(const char *filename);

#endif
