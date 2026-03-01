# rpolib

A C library written from scratch by someone learning the language. Every function here is a reimplementation — no wrappers, no shortcuts.

---

## Background

I came from Python and wanted to understand what high-level languages abstract away. Things like: why is a string just a pointer? What actually happens when you copy memory? Why does `strcpy` not check bounds? Reading about it only goes so far. Writing it is different.

This project is that process, made public.

---

## ⚠️ A note on safety

Every function here follows its **original ISO C / POSIX specification** — not a safer or modernized version.

That means `strcpy` has no bounds checking. `strncpy` won't null-terminate if `src >= n`. `strcat` trusts that you allocated enough space. This matches the documented behavior intentionally — the point is to understand *why* these functions work the way they do, including their known problems.

I know about buffer overflows. I know why `strlcpy` and `strcpy_s` exist. Safe variants will be implemented separately, for comparison.

**Not for production use.**

---

## Structure

```
rpolib/
├── include/        # headers and function declarations
├── src/            # implementations
├── tests/          # one test file per module
└── Makefile        # build and test
```

---

## Running

```bash
make        # build and run all tests
make clean  # remove binaries
make re     # full rebuild
```

Tests use a minimal `ASSERT` macro — no external libraries. Keeping it simple on purpose.

---

### Implemented

### Strings

`rpo_strlen` `rpo_strcpy` `rpo_strncpy` `rpo_strcmp`

### Memory

work in progress.

## What comes next

Strings and memory are the foundation. From here the plan is:

- Type conversion — `atoi`, `itoa`, `atof`
- Dynamic arrays — manual memory management, equivalent to Python's `list`
- Linked lists — singly and doubly linked
- Hash tables — equivalent to Python's `dict`

Each step builds on the previous one. The goal is to understand how the data structures used daily in high-level languages are actually built.

---

## References

- [The Open Group Base Specifications — Issue 8](https://pubs.opengroup.org/onlinepubs/9799919799/)
- [ISO C Standard (C11)](https://www.iso.org/standard/57853.html)
- [42 School libft](https://github.com/42School) — reference for study structure

---

**Rafael Rossano**
