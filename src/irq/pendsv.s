// https://interrupt.memfault.com/blog/cortex-m-rtos-context-switching

MAX_SYSCALL_INTERRUPT_PRIORITY equ 0b1111111

section .text

.PendSV_Handler:
                                     //TODO en cas de premier processus current_proc est NULL
    ldr     r3, current_proc     // Get the location of the current process.
    mrs r0, psp
    isb
    ldr     r2, [r3]

    cmp r2, #0
    je sch

    stmfd r0!, {r4-r11}         // Save the core registers.
    str r0, [r2]                     // Save the new top of stack into the first member of the process.

    // Call scheduler
    stmdb sp!, {r0, r3}
    mov r0, MAX_SYSCALL_INTERRUPT_PRIORITY
    msr basepri, r0
    isb
    bl schedule
    mov r0, #0
    msr basepri, r0
    ldmia sp!, {r0, r3}

    ldr r1, [r3]                     // The first item in current_proc is the task top of stack.
    ldr r0, [r1]

    ldmia r0!, {r4-r11}         // Pop the core registers.

    msr psp, r0
    isb


    bx r14

    .align 4
