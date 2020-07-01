#include <stdint.h>
#include <stddef.h>

#include "irq/irq.h"
#include "periphs/systick.h"
#include "periphs/uart.h"
#include "proc/process.h"

#include "filesystem/filesystem.h"

int main() {
    enable_irq();

    uart0_write("Main started.\n");

    fs_init();
    init_proc_table();
    systick_init(0x6FFFFF);

    while (1) {}

    return 0;
}
