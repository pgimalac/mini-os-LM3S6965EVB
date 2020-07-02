.thumb
.syntax unified
.cpu cortex-m3


.global exit
.thumb_func
exit:
    svc 0
    bx r14


.global fork
.thumb_func
fork:
    svc 1
    bx r14

.global getpid
.thumb_func
getpid:
    svc 2
    bx r14

.global open
.thumb_func
open:
    svc 3
    bx r14

.global close
.thumb_func
close:
    svc 4
    bx r14

.global write
.thumb_func
write:
    svc 5
    bx r14

.global read
.thumb_func
read:
    svc 6
    bx r14

.global lseek
.thumb_func
lseek:
    svc 7
    bx r14

.global remove
.thumb_func
remove:
    svc 8
    bx r14

.global move
.thumb_func
move:
    svc 9
    bx r14

