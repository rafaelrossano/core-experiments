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

char *rpo_strncpy(char * restrict dst, const char * restrict src, size_t n) {
    char *p = dst;

    while (n--) {
        if (*src) {
            *p++ = *src++;
        } else {
            *p++ = '\0';
        }
    }

    return dst;
}

char *rpo_strcat(char * restrict s1, const char * restrict s2) {
    char *p = s1;
    while (*s1) s1++;
    while (*s2) 
        *s1++=*s2++;
        
    return p;
}
