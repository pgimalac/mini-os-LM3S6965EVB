#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include "handlers.h"
#include "icsr.h"
#include "irq.h"
#include "periphs/systick.h"
#include "periphs/uart.h"
#include "proc/process.h"
#include "proc/scheduler.h"

void SysTick_Handler() {
    uart0_write("SysTick_Handler\n");
    systick_tick++;

    schedule();
    trigger_pendsv();
}
