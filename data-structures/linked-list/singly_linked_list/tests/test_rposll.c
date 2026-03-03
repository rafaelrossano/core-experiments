#include <stdio.h>
#include <string.h>
#include "rposll.h"

#define TEST_STRINGS_MAX_SIZE 16

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

void test_sll_create() {
    printf("\n[sll_create]\n");
    sll *list = sll_create();

    ASSERT("null head",         list->head == NULL);
    ASSERT("zero size",         list->size == 0);
}

// -- Main --

int main(void)
{
    printf("=== Running tests ===");
    
    test_sll_create();

    printf("\n=== Result: %d/%d passed ===\n",
           tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? 1 : 0;
}