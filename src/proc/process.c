#include "process.h"
#include "irq/icsr.h"
#include "irq/irq.h"
#include "periphs/uart.h"
#include "scheduler.h"
#include "tasks.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

process_t proc_table[PROC_MAX_NUM];
volatile uint8_t proc_stacks[PROC_MAX_NUM][STACK_SIZE];

process_t *current_proc = NULL;
process_t *next_proc = NULL;

// contains the 'free' pids
uint32_t free_pid[PROC_MAX_NUM];

// the number of free pids
uint32_t free_pid_number = 0;

void init_proc_table() {
    for (int proc_num = 0; proc_num < PROC_MAX_NUM; proc_num++) {
        process_t *proc = &proc_table[proc_num];
        proc->flags = 0;
        proc->pid = proc_num;
        proc->stack_end = (void *)proc_stacks[proc->pid];
        proc->stack_start = (void *)(proc->stack_end + STACK_SIZE);
    }

    for (int proc_num = PROC_MAX_NUM - 1; proc_num >= 0; proc_num--) {
        free_pid[free_pid_number++] = proc_num;
    }

    new_task(init, NULL);
}

void task_cleaner(task_func_t f, void *arg) { exit(f(arg)); }

int new_task(task_func_t f, void *arg) {
    if (free_pid_number == 0) {
        return -1;
    }

    uint32_t pid = free_pid[--free_pid_number];
    process_t *proc = &proc_table[pid];

    context_proc *ctp =
        (context_proc *)((uint8_t *)proc->stack_start - sizeof(context_proc));
    ctp->r0 = f;
    ctp->r1 = arg;
    ctp->r2 = 0;
    ctp->r3 = 0;
    ctp->r12 = 0;
    ctp->lr = 0;
    ctp->pc = task_cleaner;
    ctp->xpsr = (void *)0x21000000;

    context_soft *cts = (context_soft *)((uint8_t *)ctp - sizeof(context_soft));
    cts->r4 = 0;
    cts->r5 = 0;
    cts->r6 = 0;
    cts->r7 = 0;
    cts->r8 = 0;
    cts->r9 = 0;
    cts->r10 = 0;
    cts->r11 = 0;

    for (int i = 0; i < PROC_MAX_FD; i++) {
        proc->fds[i].inode = 0;
    }

    proc->sp = (void *)cts;

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
    memcpy((void *)proc->sp, (void *)current_proc->sp,
           current_proc->stack_start - current_proc->sp);
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
