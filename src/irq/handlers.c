#include <stdint.h>

#include "handlers.h"
#include "icsr.h"
#include "periphs/uart.h"
#include "proc/process.h"
#include "irq.h"

void SysTick_Handler() {
    uart0_write("SysTick_Handler\n");
    trigger_pendsv();
}

void PendSV_Handler() {
    uart0_write("PendSV_Handler\n");
    // full assembly
}
