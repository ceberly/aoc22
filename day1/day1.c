#include <assert.h>

#include <stdio.h>

#include <ctype.h>
#include <stdbool.h>

#include "../aoc.h"

// returns 0 when there is no more data
static unsigned next_sum(char **buffer, const char *buffer_end) {
  unsigned running_sum = 0;
  unsigned running_number = 0;

  while (*buffer != buffer_end) {
    char c = **buffer;

    if (isdigit(c)) {
      running_number = 10 * running_number + (c - '0');
      goto next;
    }

    if (c == '\n') {
      if (running_number > 0) {
        running_sum += running_number;
        running_number = 0;

        goto next;
      }

      // otherwise we have hit two new lines in a row so we're done...
      (*buffer)++;
      return running_sum;
    }

    fprintf(stderr, "Unexpected input character '%c'.\n", c);
    return 0;

  next:
    (*buffer)++;
  }

  return running_sum;
}

static void part1(char_buf_t input) {
  char *bufp = input.buf;
  char *buf_end = bufp + input.len;

  unsigned curr_sum = 0;
  unsigned max_sum = 0;

  while ((curr_sum = next_sum(&bufp, buf_end)) > 0) {
    if (curr_sum > max_sum) {
      max_sum = curr_sum;
    }
  }

  printf("day1 | part1: %u\n", max_sum);
}

static int compare(const void *a, const void *b) {
  unsigned int c, d;
  c = *(int *)a;
  d = *(int *)b;

  if (c == d)
    return 0;
  if (c > d)
    return -1;

  return 1;
}

static void part2(char_buf_t input) {
  char *bufp = input.buf;
  char *buf_end = bufp + input.len;

  unsigned curr_sum = 0;

  size_t sums_count = 0;
  size_t sums_capacity = 1000;

  unsigned *sums = malloc(sizeof(unsigned) * sums_capacity);
  assert(sums != NULL);

  while ((curr_sum = next_sum(&bufp, buf_end)) > 0) {
    if (sums_count == sums_capacity) {
      fprintf(stderr, "allocating more sums\n");
      sums_capacity *= 2;
      sums = realloc(sums, sums_capacity);
    }

    sums[sums_count++] = curr_sum;
  }

  qsort(sums, sums_count, sizeof(unsigned), compare);

  assert(sums_count >= 3);

  unsigned total_sum = 0;
  total_sum += sums[0];
  total_sum += sums[1];
  total_sum += sums[2];

  free(sums);

  printf("day1 | part2: %u\n", total_sum);
}

void day1(char_buf_t input) {
  part1(input);
  part2(input);
}
