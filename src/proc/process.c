#include "process.h"
#include "irq/irq.h"
#include "periphs/uart.h"

#include <stddef.h>
#include <stdint.h>

process_t proc_table[PROC_MAX_NUM];

process_t *current_proc = NULL;
process_t *next_proc = NULL;

int next_proc_pid = 0;

void *task(void *arg) {
    char buff[2];
    buff[1] = 0;
    buff[0] = (uint32_t)arg;
    while (1) {
        uart0_write(buff);
        for (int i = 0; i < 10000; i++){}
    }
}

void init_proc_table() {
    for (int proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        proc_table[proc_num].flags = 0;
    }

    new_task(task, (void *) 'A');
    new_task(task, (void *) 'B');
}

int new_task(task_func_t f, void *arg) {
    if (next_proc_pid == PROC_MAX_NUM) {
        return -1;
    }

    process_t *proc = proc_table + next_proc_pid;
    proc->pid = next_proc_pid;
    next_proc_pid++;

    context_proc *ctp = (context_proc *) (proc->stack + STACK_SIZE);
    ctp->r0   = (uint32_t) arg;
    ctp->r1   = 0;
    ctp->r2   = 0;
    ctp->r3   = 0;
    ctp->r12  = 0;
    ctp->lr   = 0xFFFFFFFD;
    ctp->pc   = (uint32_t) f;
    ctp->xpsr = 0x21000000;

    context_soft *cts = (context_soft *) (proc-> stack + STACK_SIZE - sizeof(context_proc));
    cts-> r4  = 0;
    cts-> r5  = 0;
    cts-> r6  = 0;
    cts-> r7  = 0;
    cts-> r8  = 0;
    cts-> r9  = 0;
    cts-> r10 = 0;
    cts-> r11 = 0;

    proc->sp    = (uint32_t *) (proc-> stack + STACK_SIZE - sizeof(context_proc) - sizeof(context_soft));

    proc->flags = 1; //TODO détailler

    return 0;
}


