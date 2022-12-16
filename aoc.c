#include <assert.h>

#include <stdlib.h>
#include <stdio.h>

// ifdef linux, windows etc...
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "aoc.h"

char_buf_t memory_map_file(const char *filename) {
  char_buf_t result = {
    .buf = NULL,
    .len = 0,
  };

  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    goto perror_fail;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    goto perror_fail;
  }

  assert(sizeof(size_t) >= sizeof(off_t));
  assert(sb.st_size >= 0);
  size_t len = (size_t)sb.st_size;

  void *map = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0); 
  assert(map != NULL);

  result.buf = map;
  result.len = len;

  return result;

perror_fail:
  perror("aoc.c: unable to map file");
  return result;
}
