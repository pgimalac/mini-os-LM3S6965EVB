#include "process.h"
#include "irq/irq.h"
#include "periphs/uart.h"
#include "irq/icsr.h"
#include "scheduler.h"

#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

process_t proc_table[PROC_MAX_NUM];
volatile uint8_t proc_stacks[PROC_MAX_NUM][STACK_SIZE];

process_t *current_proc = NULL;
process_t *next_proc = NULL;

void *task(void *arg) {
    uart0_write("TASK_BEGIN\n");

    int ret = fork();
    if (ret == -1) {
        uart0_write("returned -1\n");
    } else if (ret == 0) {
        uart0_write("returned 0\n");
    } else {
        uart0_write("returned >0\n");
        uart0_write_int(ret);
    }

    for (int j = 0; j < 50; j++) {
        uart0_write(arg);
        for (int i = 0; i <= 10000000; i++){}
    }

    exit(0);
}

void *init() {
    new_task(task, "A");
    new_task(task, "B");
    new_task(task, "C");
    new_task(task, "D");
    new_task(task, "E");

    while (1);
}

// contains the 'free' pids
uint32_t free_pid[PROC_MAX_NUM];

// the number of free pids
uint32_t free_pid_number = 0;

void init_proc_table() {
    for (int proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        process_t *proc   = &proc_table[proc_num];
        proc->flags       = 0;
        proc->pid         = proc_num;
        proc->stack_end   = (void *) proc_stacks[proc->pid];
        proc->stack_start = (void *) (proc->stack_end + STACK_SIZE);
    }

    for (int proc_num = PROC_MAX_NUM - 1; proc_num >= 0; proc_num--) {
        free_pid[free_pid_number++] = proc_num;
    }

    new_task(init, NULL);
}

int new_task(task_func_t f, void *arg) {
    if (free_pid_number == 0) {
        return -1;
    }

    uint32_t pid = free_pid[--free_pid_number];
    process_t *proc = &proc_table[pid];

    context_proc *ctp = (context_proc *) ((uint8_t*)proc->stack_start - sizeof(context_proc));
    ctp->r0   = arg;
    ctp->r1   = 0;
    ctp->r2   = 0;
    ctp->r3   = 0;
    ctp->r12  = 0;
    ctp->lr   = (void *)0xFFFFFFFD;
    ctp->pc   = f;
    ctp->xpsr = (void *)0x21000000;

    context_soft *cts = (context_soft *) ((uint8_t*)ctp - sizeof(context_soft));
    cts-> r4  = 0;
    cts-> r5  = 0;
    cts-> r6  = 0;
    cts-> r7  = 0;
    cts-> r8  = 0;
    cts-> r9  = 0;
    cts-> r10 = 0;
    cts-> r11 = 0;

    proc->sp       = (void *) cts;

    proc->flags = PROCESS_FLAGS_EXISTS;

    return 0;
}

extern void sys_fork_save_sp(void);

uint32_t sys_fork() {
    if (current_proc == NULL || free_pid_number == 0) {
        return -1;
    }

    uint32_t pid = free_pid[--free_pid_number];
    process_t *proc = &proc_table[pid];

    sys_fork_save_sp();

    proc->sp = proc->stack_start - current_proc->stack_start + current_proc->sp;
    memcpy((void *)proc->sp, (void *)current_proc->sp, current_proc->stack_start - current_proc->sp);
    proc->flags = current_proc->flags;

    return pid;
}

// add __attribute__((noreturn)) ?
void sys_exit(int status) {
    if (current_proc == NULL) {
        return;
    }

    free_pid[free_pid_number++] = current_proc->pid;
    current_proc->flags = 0;
    current_proc->sp = current_proc->stack_start;

    current_proc = NULL;

    uart0_write("sys_exit ");
    uart0_write_int(status);

    schedule();

    trigger_pendsv();
}
