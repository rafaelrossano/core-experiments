#include <stdio.h>
#include <string.h>
#include "rpomem.h"

#define BUF_SIZE 16

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

void test_memset(void) {
    printf("\n[memset]\n");
    unsigned char buf[BUF_SIZE];
    void *p;

    memset(buf, 0xAB, BUF_SIZE);
    int all_set = 1;
    for (int i = 0; i < BUF_SIZE; i++)
        if (buf[i] != 0xAB) { all_set = 0; break; }
    ASSERT("fills every byte with given value",     all_set);

    p = memset(buf, 0x00, BUF_SIZE);
    ASSERT("returns dst pointer",                   p == (void *)buf);

    memset(buf, 0x00, BUF_SIZE);
    int all_zero = 1;
    for (int i = 0; i < BUF_SIZE; i++)
        if (buf[i] != 0x00) { all_zero = 0; break; }
    ASSERT("fill with 0x00",                        all_zero);

    memset(buf, 0xFF, BUF_SIZE);
    int all_ff = 1;
    for (int i = 0; i < BUF_SIZE; i++)
        if (buf[i] != 0xFF) { all_ff = 0; break; }
    ASSERT("fill with 0xFF",                        all_ff);

    memset(buf, 0xAA, BUF_SIZE);
    memset(buf, 0x00, 0);
    int unchanged = 1;
    for (int i = 0; i < BUF_SIZE; i++)
        if (buf[i] != 0xAA) { unchanged = 0; break; }
    ASSERT("n == 0, buffer unchanged",              unchanged);

    p = memset(buf, 0x00, 0);
    ASSERT("n == 0, returns dst pointer",           p == (void *)buf);

    memset(buf, 0x00, BUF_SIZE);
    memset(buf, 0xFF, 4);
    int partial_ok = 1;
    for (int i = 0; i < 4; i++)
        if (buf[i] != 0xFF) { partial_ok = 0; break; }
    for (int i = 4; i < BUF_SIZE; i++)
        if (buf[i] != 0x00) { partial_ok = 0; break; }
    ASSERT("partial fill leaves rest untouched",    partial_ok);

}

// -- Main --

int main(void)
{
    printf("=== Running tests ===");
    test_memset();
    printf("\n=== Result: %d/%d passed ===\n",
           tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? 1 : 0;
}
