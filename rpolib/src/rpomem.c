#include "rpomem.h"

void *rpo_memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while (n--) {
        *p = (unsigned char)c;
        p++;
    }
    return s;
}

void *rpo_memcpy(char *dst, const char *src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (unsigned char *)src;

    while (n--) {
        *d++=*s++;
    }
    return dst;
}