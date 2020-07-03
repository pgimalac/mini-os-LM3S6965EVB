// https://interrupt.memfault.com/blog/cortex-m-rtos-context-switching
.thumb
.syntax unified
.cpu cortex-m3
.extern current_proc
.extern next_proc
.global PendSV_Handler

.thumb_func
PendSV_Handler:
    mrs r0, psp
    ldr r3, =current_proc         // Get the location of the current process.
    isb
    ldr r2, [r3]

    cbz r2, sch

    stmfd r0!, {r4-r11}         // Save the core registers.
    str r0, [r2]                     // Save the new top of stack into the first member of the process.

    sch:
    ldr r3, =next_proc
    ldr r2, [r3]
    ldr r0, [r2]

    ldmia r0!, {r4-r11}         // Pop the core registers.

    msr psp, r0
    isb

    ldr r3, =current_proc
    ldr r2, =next_proc
    ldr r2, [r2]
    str r2, [r3]

    // those three lines are supposed to enable unprivileged thread mode
    // not very sure it works

    //mrs r0, CONTROL
    //orr r0, #1
    //msr CONTROL, r0

    ldr r14, =0xFFFFFFFD

    bx r14

    .align 4
