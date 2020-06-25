#include <stdint.h>

#include "handlers.h"
#include "icsr.h"
#include "periphs/uart.h"
#include "proc/process.h"
#include "irq.h"
#include "proc/scheduler.h"

void SysTick_Handler() {
    uart0_write("SysTick_Handler\n");
    schedule();
    trigger_pendsv();
}
