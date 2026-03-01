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
    *s1 = '\0';
    return p;
}

char *rpo_strncat(char * restrict s1, const char * restrict s2, size_t n) {
    char *p = s1;

    while (*s1) s1++;
    while (n-- && *s2) *s1++=*s2++;
    *s1 = '\0';
    return p;
}

int rpo_strcmp(const char * s1, const char * s2) {
    while (*s1 && *s1==*s2) {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

int rpo_strncmp(const char * s1, const char * s2, size_t n) {
    if (n==0) return 0;
    while (--n && *s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *rpo_strchr(const char *str, int c) {
    while (*str) {
        if (*str == (char)c) return (char *)str;
        str++;
    }
    if (*str == (char)c) return (char *)str;
    return NULL;
}

char *rpo_strrchr(const char *str, int c) {
    char *last_occurrence = NULL;
    while (*str) {
        if (*str == (char)c) last_occurrence = (char *)str;
        str++;
    }
    if (*str == (char)c) return (char *)str;
    return last_occurrence;
}

char *rpo_strstr(const char *s1, const char *s2) {
    if (!*s2) return (char *)s1;
    while (*s1) {
        const char *p1 = s1;
        const char *p2 = s2;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) return (char *)s1;
        s1++;
    }
    return NULL;
    // Try KMP after getting better at malloc.
}