#include <stdio.h>
#include <string.h>
#include "rpostr.h"

static int tests_run    = 0;
static int tests_failed = 0;

#define ASSERT(description, condition)              \
    do {                                            \
        tests_run++;                                \
        if (!(condition)) {                         \
            tests_failed++;                         \
            printf("  FAIL: %s\n", description);   \
        } else {                                    \
            printf("  OK:   %s\n", description);   \
        }                                           \
    } while (0)

// -- Tests --

void test_strlen(void) {
    printf("\n[rpo_strlen]\n");
    ASSERT("normal string",         rpo_strlen("hello") == 5);
    ASSERT("empty string",          rpo_strlen("") == 0);
    ASSERT("spaced string",         rpo_strlen("a b c") == 5);
    ASSERT("single space string",   rpo_strlen(" ") == 1);
}

void test_strcpy(void) {
    printf("\n[rpo_strcpy]\n");
    char buf[64];
    char *p;

    p = rpo_strcpy(buf, "Hello, World!");
    ASSERT("correct copy",          strcmp(buf, "Hello, World!") == 0);
    ASSERT("correct return",        p == buf);
}

// -- Main --

int main(void)
{
    printf("=== Running tests ===");
    test_strlen();
    test_strcpy();
    //test_strcmp();
    printf("\n=== Result: %d/%d passed ===\n",
           tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? 1 : 0;
}