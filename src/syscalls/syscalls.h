#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include "filesystem/filesystem.h"

extern void *syscalls[];

#define SYS_EXIT 0
#define SYS_FORK 1

void sys_exit(int status);
uint32_t sys_fork();
uint32_t sys_getpid();
int sys_open(char *name, int append);
void sys_close(int fd);
int sys_write(int fd, char *buff, int len);
int sys_read(int fd, char *buff, int len);
int sys_lseek(int fd, uint32_t pos, int whence);
void sys_remove(char *name);
void sys_move(char *name, char *newname);
file_view * sys_iter_files(file_view * view);

#endif
