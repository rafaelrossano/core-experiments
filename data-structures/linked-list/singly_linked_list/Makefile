CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -fsanitize=address
SRC = src/rposll.c
TEST = tests/test_rposll.c
BIN = test_runner

.PHONY: all test clean re

all: test

test: $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)

re: clean all
