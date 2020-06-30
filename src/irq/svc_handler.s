.thumb
.syntax unified
.cpu cortex-m3
.extern syscalls
.global SVC_Handler

.thumb_func
SVC_Handler:
    stmfd r13!, {r4-r5, r14}

    tst lr, #4
    ite eq
    mrseq r4, msp
    mrsne r4, psp

    // *(*($r4+24)-2) & 0x000000ff

    add r5, r4, #24
    ldr r5, [r5]
    sub r5, #2
    ldr r5, [r5]
    and r5, 0x000000ff

    ldr r6, =4
    mul r5, r6
    ldr r6, =syscalls
    add r5, r6

    ldr r5, [r5]
    blx r5

    tst lr, #4
    ite eq
    mrseq r4, msp
    mrsne r4, psp

    str r0, [r4]

    ldmia r13!, {r4-r5, r14}

    bx r14
