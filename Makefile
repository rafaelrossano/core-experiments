CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

SRC     = src/rpostr.c
TEST    = tests/test_rpostr.c
BIN     = test_runner

.PHONY: all test clean re

all: test

test: $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)

re: clean all