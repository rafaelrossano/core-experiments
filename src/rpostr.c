#include "rpostr.h"

size_t rpo_strlen(const char *str)
{
    size_t str_len;

    str_len = 0;
    while (str[str_len]) {
        str_len++;
    }
    return str_len;
}

char *rpo_strcpy(char * restrict dst, const char * restrict src) {
    char *p = dst;

    while (*src != '\0') {
        *p = *src;
        p++;
        src++;
    }

    *p = *src;
    return dst;
}
