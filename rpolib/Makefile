CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

test: test_str test_mem

test_str: src/rpostr.c tests/test_rpostr.c
	$(CC) $(CFLAGS) src/rpostr.c tests/test_rpostr.c -o test_str
	./test_str

test_mem: src/rpomem.c tests/test_rpomem.c
	$(CC) $(CFLAGS) src/rpomem.c tests/test_rpomem.c -o test_mem
	./test_mem

clean:
	rm -f test_str test_mem

re: clean test

.PHONY: test test_str test_mem clean re