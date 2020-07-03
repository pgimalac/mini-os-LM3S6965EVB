#include <stdlib.h>

#include "syscalls.h"
#include "proc/process.h"

uint32_t sys_getpid() {
    return current_proc->pid;
}

void *syscalls[] = {
    sys_exit,
    sys_fork,
    sys_getpid,
    sys_open,
    sys_close,
    sys_write,
    sys_read,
    sys_lseek,
    sys_remove,
    sys_move,
    sys_iter_files
};
