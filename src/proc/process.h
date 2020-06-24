#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#ifndef PROC_MAX_NUM
    #define PROC_MAX_NUM 16
#endif

#ifndef STACK_SIZE
    #define STACK_SIZE 1024
#endif

typedef void *(*task_func_t)(void *);

typedef struct {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
} context_proc;

typedef struct {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
} context_soft;


// https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/6199b72fbf57a7c5b3d7b195a3bd1446779314cd/tasks.c
// tskTaskControlBlock
typedef struct {
    volatile uint32_t *sp;
    uint32_t flags;
    uint32_t pid;
    uint8_t stack[STACK_SIZE];
} process_t;

extern process_t proc_table[PROC_MAX_NUM];
extern process_t *current_proc;
extern process_t *next_proc;

void init_proc_table();

int new_task(task_func_t f, void *arg);

#endif
