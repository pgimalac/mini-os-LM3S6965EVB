#include "uart.h"

#include <stdint.h>

int uart0_write(char *txt) {
    char *ptr;

    for (ptr = txt; *ptr; ptr++)
        UART0_ADDR = (uint32_t) *ptr;

    return (int) (ptr - txt);
}
