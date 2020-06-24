#include <stdint.h>
#include <stddef.h>

#include "irq/irq.h"
#include "periphs/systick.h"
#include "periphs/uart.h"
#include "proc/process.h"

int main() {
    uart0_write("Main started.");

    enable_irq();
    init_proc_table();
    systick_init(0xFFFFF);

    while (1) {}

    return 0;
}
