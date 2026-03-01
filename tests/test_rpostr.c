#include <stdio.h>
#include <string.h>
#include "rpostr.h"

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

void test_strlen(void) {
    printf("\n[rpo_strlen]\n");
    ASSERT("normal string",         rpo_strlen("hello") == 5);
    ASSERT("empty string",          rpo_strlen("") == 0);
    ASSERT("spaced string",         rpo_strlen("a b c") == 5);
    ASSERT("single space string",   rpo_strlen(" ") == 1);
}

void test_strcpy(void) {
    printf("\n[rpo_strcpy]\n");
    char buf[TEST_STRINGS_MAX_SIZE];
    char *p;

    p = rpo_strcpy(buf, "Hello, World!");
    ASSERT("correct copy",          strcmp(buf, "Hello, World!") == 0);
    ASSERT("correct return (dst)",  p == buf);

    p = rpo_strcpy(buf, "");
    ASSERT("empty string",          strcmp(buf, "") == 0);
     ASSERT("correct return (dst)",  p == buf);
}

void test_strncpy(void) {
    printf("\n[rpo_strncpy]\n");
    char buf[TEST_STRINGS_MAX_SIZE];
    char *p;
    size_t nbytes;
    char aux_buf[TEST_STRINGS_MAX_SIZE] = {0};

    nbytes = 5;

    p = rpo_strncpy(buf, "Hello, World!", nbytes);
    ASSERT("correct return (dst)",  p==buf);
    ASSERT("correct num of bytes copied",               memcmp(buf, "Hello", nbytes) == 0);
    
    rpo_strncpy(buf, "abc", nbytes);
    ASSERT("filled with NULL characters if n > src",    memcmp(buf, aux_buf, nbytes));

    nbytes = 0;
    char *buffer_2 = "Hello";
    strncpy(buffer_2, ", World!", nbytes);
    ASSERT("0 bytes passed",        strcmp(buffer_2, "Hello") == 0);
}

void test_strcat(void) {
    printf("\n[rpo_strcat]\n");
    char s1[TEST_STRINGS_MAX_SIZE] = "Hello,";
    char s2[TEST_STRINGS_MAX_SIZE] = " World!";
    char empty_string[TEST_STRINGS_MAX_SIZE] = "";
    char *p;

    p = rpo_strcat(s1, s2);
    ASSERT("concatenation",         strcmp(s1, "Hello, World!") == 0);
    ASSERT("correct return (s1)",   p==s1);

    strcpy(s1, "Hello,");
    rpo_strcat(s1, empty_string);
    ASSERT("empty s2 string",       strcmp(s1, "Hello,") == 0);
    
    strcpy(s2, " World!");
    rpo_strcat(empty_string, s2);
    ASSERT("empty s1 string",       strcmp(empty_string, " World!") == 0);
}

// -- Main --

int main(void)
{
    printf("=== Running tests ===");
    test_strlen();
    test_strcpy();
    test_strncpy();
    test_strcat();
    printf("\n=== Result: %d/%d passed ===\n",
           tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? 1 : 0;
}