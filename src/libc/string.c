#include "string.h"

#include <stdint.h>

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t buffer[n];

    memcpy(buffer, src, n);
    memcpy(dest, buffer, n);

    return dest;
}

char *strcpy(char *dest, const char *src) {
    while (*src != 0) {
        *dest++ = *src++;
    }

    *dest++ = 0;

    return dest;
}


void *memcpy(void *dest, const void *src, size_t n) {
    while (n > 0) {
        *(uint8_t *)dest++ = *(uint8_t *)src++;
        n--;
    }

    return dest;
}


void *memset(void *s, int c, size_t n) {
    while (n > 0) {
        *(uint8_t *)s++ = (uint8_t)c;
        n--;
    }

    return s;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 == *s2) {
            s1++;
            s2++;
        } else if (*s1 < *s2) {
            return -1;
        } else {
            return 1;
        }
    }

    if (*s1 == 0) {
        if (*s2 == 0) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}
