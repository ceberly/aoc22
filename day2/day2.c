#include <assert.h>
#include <stdio.h>

#include "../aoc.h"

static int part1_possible_games[] = {
  3 + 0, // rock - scissors
  2 + 6, // rock - paper
  1 + 3, // rock - rock

  3 + 6, // paper - scissors
  2 + 3, // paper - paper
  1 + 0, // paper - rock

  3 + 3, // scissors - scissors
  2 + 0, // scissors - paper 
  1 + 6, // scissors - rock 
};

static int part2_possible_games[] = {
  2 + 6, // rock - Z
  1 + 3, // rock - Y
  3 + 0, // rock - X

  3 + 6, // paper - Z
  2 + 3, // paper - Y
  1 + 0, // paper - X

  1 + 6, // scissors - Z
  3 + 3, // scissors - Y
  2 + 0, // scissors - X
};

void part1(char_buf_t input) {
  char *bufp = input.buf;
  char *buf_end = input.buf + input.len;

  int total_score = 0;

  while (buf_end - bufp >= 3) {
    char theirs = *bufp++;
    char ours = *++bufp;

    int game_score = part1_possible_games[((theirs - 'A') * 3) + ('Z' - ours)];
    total_score += game_score;

    if (++bufp == buf_end) {
      break;
    }

    bufp++;
  }

  printf("day2 | part1: %d\n", total_score);
}

void part2(char_buf_t input) {
  char *bufp = input.buf;
  char *buf_end = input.buf + input.len;

  int total_score = 0;

  while (buf_end - bufp >= 3) {
    char theirs = *bufp++;
    char ours = *++bufp;

    int game_score = part2_possible_games[((theirs - 'A') * 3) + ('Z' - ours)];
    total_score += game_score;

    if (++bufp == buf_end) {
      break;
    }

    bufp++;
  }

  printf("day2 | part2: %d\n", total_score);
}

void day2(char_buf_t input) {
  part1(input);
  part2(input);
}
