#include "uart.h"

#include <stdint.h>

void uart0_write_int(int arg) {
    if (arg == 0) {
        UART0_ADDR = '0';
    }

    while (arg != 0) {
        UART0_ADDR = (arg % 10) + '0';
        arg /= 10;
    }
    UART0_ADDR = '\n';
}

int uart0_write(char *txt) {
    char *ptr;

    for (ptr = txt; *ptr; ptr++)
        UART0_ADDR = (uint32_t)*ptr;

    return (int)(ptr - txt);
}
