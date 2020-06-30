#include "scheduler.h"
#include "periphs/uart.h"

#include <unistd.h>

void schedule() {
    uart0_write("SCHEDULE_START\n");
    for (uint32_t proc_num = current_proc == NULL ? 1 : current_proc->pid + 1; proc_num < PROC_MAX_NUM; proc_num++) {
        process_t *proc = &proc_table[proc_num];
        if (proc->flags & 1 && current_proc != proc) {
            next_proc = proc;
            uart0_write("SCHEDULE_END\n");
            return;
        }
    }

    for (uint32_t proc_num = 1; proc_num < (current_proc == NULL ? 1 : current_proc->pid); proc_num++) {
        process_t *proc = &proc_table[proc_num];
        if (proc->flags & 1 && current_proc != proc) {
            next_proc = proc;
            uart0_write("SCHEDULE_END\n");
            return;
        }
    }

    next_proc = &proc_table[0];
}
