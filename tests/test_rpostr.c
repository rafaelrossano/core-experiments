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
    ASSERT("correct return (dst)",              p == buf);
    ASSERT("correct num of bytes copied",       memcmp(buf, "Hello", nbytes) == 0);
    ASSERT("no null terminator if n < src",     buf[5] != '\0' || memcmp(buf, "Hello", 5) == 0);

    char buffer_2[TEST_STRINGS_MAX_SIZE];
    rpo_strncpy(buffer_2, "abc", nbytes);
    ASSERT("src copied correctly",                      memcmp(buffer_2, "abc", 3) == 0);
    ASSERT("filled with NULL characters if n > src",    memcmp(buffer_2 + 3, aux_buf, nbytes - 3) == 0);

    char buffer_3[TEST_STRINGS_MAX_SIZE] = "Hello";
    rpo_strncpy(buffer_3, ", World!", 0);
    ASSERT("n == 0, nothing copied",            strcmp(buffer_3, "Hello") == 0);
}

void test_strcat(void) {
    printf("\n[rpo_strcat]\n");
    char s1[TEST_STRINGS_MAX_SIZE] = "Hello,";
    char s2[TEST_STRINGS_MAX_SIZE] = " World!";
    char empty_string[TEST_STRINGS_MAX_SIZE] = "";
    char *p;

    p = rpo_strcat(s1, s2);
    ASSERT("concatenation",                     strcmp(s1, "Hello, World!") == 0);
    ASSERT("correct return (s1)",               p == s1);
    ASSERT("null terminated",                   s1[strlen(s1)] == '\0');

    strcpy(s1, "Hello,");
    rpo_strcat(s1, empty_string);
    ASSERT("empty s2 string",                   strcmp(s1, "Hello,") == 0);

    strcpy(s1, "");
    rpo_strcat(s1, "World!");
    ASSERT("empty s1 string",                   strcmp(s1, "World!") == 0);

    strcpy(s1, "");
    rpo_strcat(s1, empty_string);
    ASSERT("both empty",                        strcmp(s1, "") == 0);
}

void test_strncat(void) {
    printf("\n[rpo_strncat]\n");
    char s1[TEST_STRINGS_MAX_SIZE] = "Hello,";
    char *p;
    size_t nbytes;

    nbytes = 7;
    p = rpo_strncat(s1, " World!", nbytes);
    ASSERT("concatenation",                     strcmp(s1, "Hello, World!") == 0);
    ASSERT("correct return (s1)",               p == s1);
    ASSERT("null terminated",                   s1[strlen(s1)] == '\0');

    strcpy(s1, "Hello,");
    rpo_strncat(s1, " World!", 3);
    ASSERT("n < src, partial copy",             strcmp(s1, "Hello, Wo") == 0);
    ASSERT("n < src, null terminated",          s1[strlen(s1)] == '\0');

    strcpy(s1, "Hello,");
    rpo_strncat(s1, " Hi", 10);
    ASSERT("n > src, copies until src null",    strcmp(s1, "Hello, Hi") == 0);
    ASSERT("n > src, null terminated",          s1[strlen(s1)] == '\0');

    char t3[TEST_STRINGS_MAX_SIZE] = {'a', 'b', 'c'};
    rpo_strncat(t3, "xyz", 0);
    ASSERT("n == 0, null terminated added",     strcmp(t3, "abc") == 0);

    strcpy(s1, "Hello,");
    rpo_strncat(s1, "", 5);
    ASSERT("empty s2",                          strcmp(s1, "Hello,") == 0);
}

void test_strcmp(void) {
    printf("\n[rpo_strcmp]\n");

    ASSERT("equal strings",                     rpo_strcmp("abc", "abc") == 0);
    ASSERT("empty strings",                     rpo_strcmp("", "") == 0);
    ASSERT("empty s1",                          rpo_strcmp("", "abc") < 0);
    ASSERT("empty s2",                          rpo_strcmp("abc", "") > 0);
    ASSERT("s1 less than s2",                   rpo_strcmp("abc", "abd") < 0);
    ASSERT("s1 greater than s2",                rpo_strcmp("abd", "abc") > 0);
    ASSERT("s1 prefix of s2",                   rpo_strcmp("abc", "abcd") < 0);
    ASSERT("s2 prefix of s1",                   rpo_strcmp("abcd", "abc") > 0);
    ASSERT("single char equal",                 rpo_strcmp("a", "a") == 0);
    ASSERT("single char less",                  rpo_strcmp("a", "b") < 0);
    ASSERT("single char greater",               rpo_strcmp("b", "a") > 0);
    ASSERT("unsigned char comparison",          rpo_strcmp("\x80", "\x01") > 0);
}

void test_strncmp(void) {
    printf("\n[rpo_strncmp]\n");
    size_t nbytes;

    nbytes = 3;
    ASSERT("equal strings",                     rpo_strncmp("abc", "abc", nbytes) == 0);
    ASSERT("empty strings",                     rpo_strncmp("", "", nbytes) == 0);
    ASSERT("empty s1",                          rpo_strncmp("", "abc", nbytes) < 0);
    ASSERT("empty s2",                          rpo_strncmp("abc", "", nbytes) > 0);
    ASSERT("s1 less than s2",                   rpo_strncmp("abc", "abd", nbytes) < 0);
    ASSERT("s1 greater than s2",                rpo_strncmp("abd", "abc", nbytes) > 0);
    ASSERT("n == 0",                            rpo_strncmp("abc", "xyz", 0) == 0);
    ASSERT("n < difference position",           rpo_strncmp("abcX", "abcY", nbytes) == 0);
    ASSERT("n > strlen",                        rpo_strncmp("abc", "abc", 10) == 0);
    ASSERT("s1 prefix of s2",                   rpo_strncmp("abc", "abcd", 4) < 0);
    ASSERT("s2 prefix of s1",                   rpo_strncmp("abcd", "abc", 4) > 0);
    ASSERT("unsigned char comparison",          rpo_strncmp("\x80", "\x01", 1) > 0);
}

void test_strchr(void) {
    printf("\n[rpo_strchr]\n");
    const char *str = "Hello, World!";

    ASSERT("char found",                rpo_strchr(str, 'W') == str + 7);
    ASSERT("first occurrence",          rpo_strchr(str, 'l') == str + 2);
    ASSERT("first char",                rpo_strchr(str, 'H') == str);
    ASSERT("last char",                 rpo_strchr(str, '!') == str + 12);
    ASSERT("char not found",            rpo_strchr(str, 'z') == NULL);
    ASSERT("empty string",              rpo_strchr("", 'a') == NULL);
    ASSERT("null terminator search",    rpo_strchr(str, '\0') == str + 13);
}

void test_strrchr(void) {
    printf("\n[rpo_strrchr]\n");
    const char *str = "Hello, World!";

    ASSERT("char found",                rpo_strrchr(str, 'W') == str + 7);
    ASSERT("last occurrence",           rpo_strrchr(str, 'l') == str + 10);
    ASSERT("first char",                rpo_strrchr(str, 'H') == str);
    ASSERT("last char",                 rpo_strrchr(str, '!') == str + 12);
    ASSERT("char not found",            rpo_strrchr(str, 'z') == NULL);
    ASSERT("empty string",              rpo_strrchr("", 'a') == NULL);
    ASSERT("null terminator search",    rpo_strrchr(str, '\0') == str + 13);
}

// -- Main --

int main(void)
{
    printf("=== Running tests ===");
    test_strlen();
    test_strcpy();
    test_strncpy();
    test_strcat();
    test_strncat();
    test_strcmp();
    test_strncmp();
    test_strchr();
    test_strrchr();
    printf("\n=== Result: %d/%d passed ===\n",
           tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? 1 : 0;
}