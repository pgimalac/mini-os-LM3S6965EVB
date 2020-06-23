#include <stdint.h>

#include "handlers.h"
#include "icsr.h"
#include "periphs/uart.h"

void SysTick_Handler() {
    uart0_write("SysTick_Handler\n");

    static int count = 0;

    if (count % 3 == 0) {
        trigger_pendsv();
    }

    count++;
}

void PendSV_Handler() {
    uart0_write("PendSV_Handler\n");
}
