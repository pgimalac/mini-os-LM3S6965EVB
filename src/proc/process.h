#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#ifndef PROC_MAX_NUM
    #define PROC_MAX_NUM 16
#endif

// STACK_SIZE is the number of bytes in the stack of one process
#ifndef STACK_SIZE
    #define STACK_SIZE 1024
#endif

#define PROCESS_FLAGS_EXISTS   1

typedef int (*task_func_t)(void *);

typedef struct {
    void *r0;
    void *r1;
    void *r2;
    void *r3;
    void *r12;
    void *lr;
    void *pc;
    void *xpsr;
} context_proc;

typedef struct {
    void *r4;
    void *r5;
    void *r6;
    void *r7;
    void *r8;
    void *r9;
    void *r10;
    void *r11;
} context_soft;

#define PROC_MAX_FD 16
#define PROC_USED_FD (1 << 31)

typedef struct {
    int inode;
    int cursor;
} proc_file;

// https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/6199b72fbf57a7c5b3d7b195a3bd1446779314cd/tasks.c
// tskTaskControlBlock
typedef struct {
    volatile void *sp;
    uint32_t flags;
    uint32_t pid;
    proc_file fds[PROC_MAX_FD];
    void *stack_start;
    void *stack_end;
} process_t;

extern process_t proc_table[PROC_MAX_NUM];
extern volatile uint8_t proc_stacks[PROC_MAX_NUM][STACK_SIZE];
extern process_t *current_proc;
extern process_t *next_proc;

void init_proc_table();

int new_task(task_func_t, void *);

#endif
