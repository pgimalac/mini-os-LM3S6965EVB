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

typedef struct {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t ip;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;

    } hw_context ;

typedef struct  {
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t v4;
    uint32_t v5;
    uint32_t v6;
    uint32_t v7;
    uint32_t v8;
    } sw_context ;


extern process_t proc_table[PROC_MAX_NUM];
extern int current_proc;

void init_proc_table();

int new_task(task_func_t f, void *arg);

#endif
