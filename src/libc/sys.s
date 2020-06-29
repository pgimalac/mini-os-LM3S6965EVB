#include <syscalls/syscalls.h>
.thumb
.syntax unified
.cpu cortex-m3

.macro mksc name sysc num

.extern \sysc
.global \name

.thumb_func
\name :
    svc \num
    bx r14

.endm

mksc exit SYS_EXIT 1
mksc fork SYS_FORK 2
