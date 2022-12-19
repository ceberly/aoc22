DAYS=day1/day1.c day2/day2.c

.PHONY: test_heap

default:
	clang -O2 -g -Wall -Werror -Wextra -std=c11 \
		-fsanitize=address,undefined main.c aoc.c ${DAYS} -o aoc

test_heap:
	clang -DTEST -O2 -g -Wall -Werror -Wextra -std=c11 \
		-fsanitize=address,undefined heap.c -o test_heap && ./test_heap

format:
	clang-format -i *.h *.c day*/*.c
