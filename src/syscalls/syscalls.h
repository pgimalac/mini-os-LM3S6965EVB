#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

extern void *syscalls[];

#define SYS_EXIT 0
#define SYS_FORK 1

void sys_exit(int status);
uint32_t sys_fork();

#endif
