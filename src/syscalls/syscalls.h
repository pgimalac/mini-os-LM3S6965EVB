#ifndef SYSCALLS_H
#define SYSCALLS_H

extern void *syscalls[];

#define SYS_EXIT 0
#define SYS_FORK 1

void sys_exit(int status);
int sys_fork();

#endif
