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

typedef struct __attribute__((packed, aligned(4))) {

} context_proc;

typedef struct __attribute__((packed, aligned(4))) {

} context_soft;

typedef struct {
    uint32_t flags;
    uint32_t pid;
    char stack[STACK_SIZE];
} process_t;

extern process_t proc_table[PROC_MAX_NUM];
extern int current_proc;

void init_proc_table();

int new_task(task_func_t f, void *arg);

#endif
