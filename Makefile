DAYS=day1/day1.c day2/day2.c

default:
	clang -O2 -g -Wall -Werror -Wextra -std=c11 \
		-fsanitize=address,undefined main.c aoc.c ${DAYS} -o aoc

format:
	clang-format -i *.h *.c day*/*.c
