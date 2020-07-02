#include "filesystem/filesystem.h"
#include "proc/process.h"

#include <unistd.h>

int sys_open(char *name, int append) {
    int inode = fs_get_inode(name);
    if (inode == -1) {
        inode = fs_create(name);
        if (inode == -1) {
            return -1;
        }
    }

    int fd;
    for (fd = 0; fd < PROC_MAX_FD; fd++) {
        if (!(current_proc->fds[fd].inode & PROC_USED_FD)) {
            break;
        }
    }

    if (fd >= PROC_MAX_FD) {
        return -1;
    }

    file_view v;
    fs_get_view(inode, &v);

    current_proc->fds[fd].inode = inode | PROC_USED_FD;
    current_proc->fds[fd].cursor = append ? v.size : 0;

    return fd;
}

void sys_close(int fd) {
    current_proc->fds[fd].inode &= ~PROC_USED_FD;
}

int sys_write(int fd, char *buff, int len) {
    uint32_t size = fs_write(current_proc->fds[fd].inode & ~PROC_USED_FD,
                             current_proc->fds[fd].cursor,
                             buff, len);
    current_proc->fds[fd].cursor += size;
    return size;
}

int sys_read(int fd, char *buff, int len) {
    uint32_t size = fs_read(current_proc->fds[fd].inode & ~PROC_USED_FD,
                            current_proc->fds[fd].cursor,
                            buff, len);
    current_proc->fds[fd].cursor += size;
    return size;
}

int sys_lseek(int fd, int pos, int whence) {
    proc_file *file = &current_proc->fds[fd];
    file_view view;
    if (fs_get_view(file->inode & ~PROC_USED_FD, &view) == NULL) {
        close(fd);
        return -1;
    }

    if (whence == SEEK_SET) {
        if (pos < 0) {
            file->cursor = 0;
        } else {
            file->cursor = (uint32_t)pos > view.size ? view.size : (uint32_t)pos;
        }
    } else if (whence == SEEK_CUR) {
        if (pos < 0) {
            file->cursor = file->cursor + pos < 0 ? 0 : file->cursor + pos;
        } else {
            file->cursor = (uint32_t)file->cursor + pos > view.size ? view.size : (uint32_t)file->cursor + pos;
        }
    } else if (whence == SEEK_END) {
        if (pos < 0) {
            file->cursor = (uint32_t)(-pos) > view.size ? view.size : (uint32_t)pos + view.size;
        } else {
            file->cursor = view.size;
        }
    }

    return file->cursor;
}

void sys_remove(char *name) {
    int node = fs_get_inode(name);
    if (node != -1) {
        fs_remove(node);
    }
}

void sys_move(char *name, char *newname) {
    int node = fs_get_inode(name);
    if (node != -1) {
        fs_move(node, newname);
    }
}

file_view * sys_iter_files(file_view * view) {
    return fs_iter(view);
}
