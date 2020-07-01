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
