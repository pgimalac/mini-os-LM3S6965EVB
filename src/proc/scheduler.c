#include "scheduler.h"

void schedule() {
    int proc_num;
    process_t *proc;

    for (proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        proc = &proc_table[proc_num];
        if (proc->flags & 1 && current_proc != proc) {
            current_proc = proc;
        }
    }
}
