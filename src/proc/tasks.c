#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "periphs/uart.h"
#include "proc/process.h"

int task2(void *arg) {
    int fd = open((char *)arg, 0);
    if (fd == -1) {
        return 1;
    }
    uart0_write_int(fd);

    while (1) {
        write(fd, "TRUC", 4);
        uart0_write("write\n");

        for (int i = 0; i < 100000000; i++);
    }
}

#define BUFF_SIZE 1000
int task1(void *arg) {
    int fd = open((char *)arg, 0);
    if (fd == -1) {
        return 1;
    }
    uart0_write_int(fd);

    char buffer[BUFF_SIZE];

    while (1) {
        lseek(fd, 0, SEEK_SET);
        int len = read(fd, buffer, BUFF_SIZE-2);
        buffer[len] = '\n';
        buffer[len+1] = 0;

        uart0_write("read\n");
        uart0_write(buffer);

        for (int i = 0; i < 300000000; i++);
    }
}

int task(void *arg) {
    uart0_write("TASK_BEGIN\n");

    uint32_t pid = getpid();
    uart0_write("my pid is ");
    uart0_write_int(pid);

    // int ret = fork();
    // if (ret == -1) {
    //     uart0_write("returned -1\n");
    // } else if (ret == 0) {
    //     uart0_write("returned 0\n");
    // } else {
    //     uart0_write("returned >0\n");
    //     uart0_write_int(ret);
    // }

    for (int j = 0; j < 50; j++) {
        uart0_write(arg);
        for (int i = 0; i <= 10000000; i++){}
    }

    return 0;
}

int init() {
    // new_task(task, "A");
    // new_task(task, "B");
    // new_task(task, "C");
    // new_task(task, "D");
    // new_task(task, "E");
    // new_task(task2, "test");
    new_task(task1, "test");

    while (1);
}

