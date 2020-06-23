#include "process.h"
#include "irq/irq.h"

#include <stdint.h>

process_t proc_table[PROC_MAX_NUM];

int current_proc = 0;

void init_proc_table() {
    for (int proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        proc_table[proc_num].flags = 0;
    }
}

int new_task(task_func_t f, void *arg) {
    int proc_num;
    for (proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        if (proc_table[proc_num].flags == 0) {
            break;
        }
    }

    if (proc_num == PROC_MAX_NUM) {
        return -1;
    }

    static uint32_t new_pid = 0;

    process_t *proc = proc_table + proc_num;
    proc->pid = new_pid++;

    //TODO
}
