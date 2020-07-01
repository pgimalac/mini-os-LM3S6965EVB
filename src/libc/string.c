#include "string.h"

#include <stdint.h>

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t buffer[n];

    memcpy(buffer, src, n);
    memcpy(dest, buffer, n);

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

