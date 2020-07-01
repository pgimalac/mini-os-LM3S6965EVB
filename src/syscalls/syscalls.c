#include <stdlib.h>

#include "syscalls.h"
#include "proc/process.h"

uint32_t sys_getpid() {
    return current_proc->pid;
}

void *syscalls[] = {
    sys_exit,
    sys_fork,
    sys_getpid
};
