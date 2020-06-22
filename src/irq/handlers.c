#include <stdint.h>

#include "handlers.h"
#include "periphs/uart.h"

void SysTick_Handler(void) {
    uart0_write("A");
}
