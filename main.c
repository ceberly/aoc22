#include <stdio.h>
#include <stdlib.h>

#include "aoc.h"

void day1(char_buf_t);
void day2(char_buf_t);

void do_challenge() {
  day1(memory_map_file("day1/input.txt"));
  day2(memory_map_file("day2/input.txt"));
}

int main(void) {
  do_challenge();

  // do_perf_challenge()

  return EXIT_SUCCESS;
}
