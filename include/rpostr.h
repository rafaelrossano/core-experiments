#ifndef RPOSTR_H
#define RPOSTR_H

#include <unistd.h> // size_t

size_t rpo_strlen(const char *str);

char *rpo_strcpy(char * restrict dst, const char * restrict src);

char *rpo_strncpy(char * restrict dst, const char * restrict src, size_t n);

char *rpo_strcat(char * restrict s1, const char * restrict s2);

char *rpo_strncat(char * restrict s1, const char * restrict s2, size_t n);

int rpo_strcmp(const char * restrict s1, const char * restrict s2);

#endif