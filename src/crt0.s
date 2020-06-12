.thumb
.syntax unified
.cpu cortex-m3
.global _start

.thumb_func
_start:
	ldr r0, =_stack
	mov sp, r0
	bl init_bss
	bl copy_data
	bl main

_loop:	b _loop
