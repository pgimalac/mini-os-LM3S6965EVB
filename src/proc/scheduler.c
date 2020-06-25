#include "scheduler.h"

void schedule() {
    for (uint32_t proc_num = current_proc == 0 ? 0 : current_proc->pid + 1; proc_num < PROC_MAX_NUM; proc_num++) {
        process_t *proc = &proc_table[proc_num];
        if (proc->flags & 1 && current_proc != proc) {
            next_proc = proc;
            return;
        }
    }

    for (uint32_t proc_num = 0; proc_num < (current_proc == 0 ? 0 : current_proc->pid); proc_num++) {
        process_t *proc = &proc_table[proc_num];
        if (proc->flags & 1 && current_proc != proc) {
            next_proc = proc;
            return;
        }
    }
}
