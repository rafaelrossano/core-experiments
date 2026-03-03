# core-experiments

Systems programming lab. Everything implemented from scratch.

Focused on building deep competence in: memory management, data structures,
allocators, OS interfaces, and concurrency.

## Structure
```
core-experiments/
├── rpolib/            # libc-like utilities: memcpy, memmove, strlen, strdup
├── data-structures/   # linked lists, hashmaps, trees — with complexity analysis
├── allocators/        # bump, free-list, arena — interaction with mmap
├── concurrency/       # threads, synchronization, lock-free structures
└── systems/           # mmap, fork, copy-on-write, signals, file descriptors
```

Each directory is an isolated micro-project.

## Engineering Standards

- No external libraries
- Document time and space complexity
- Define ownership rules explicitly
- Always check `malloc` return values
- Never return stack addresses
- Compile with `-Wall -Wextra -Werror -fsanitize=address`
- Valgrind before considering anything stable

## Goal

The goal is not *it works*.

The goal is *I understand why it works*.