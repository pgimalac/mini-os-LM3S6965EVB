#ifndef SHCSR_H
#define SHCSR_H

#include <stdint.h>

/* SYSTEM HANDLER CONTROL AND STATE REGISTER */

// https://developer.arm.com/docs/ddi0337/e/nested-vectored-interrupt-controller/nvic-programmers-model/nvic-register-descriptions

#define SHCSR_ADDR     (*(volatile uint32_t *) 0xE000ED24)

#define BUSFAULTENA    (1 << 17)
#define MEMFAULTENA    (1 << 16)
#define SVCALLPENDED   (1 << 15)
#define BUSFAULTPENDED (1 << 14)
#define MEMFAULTPENDED (1 << 13)
#define USGFAULTPENDED (1 << 12)
#define SYSTICKACT     (1 << 11)
#define PENDSVACT      (1 << 10)
#define MONITORACT     (1 << 8)
#define SVCALLACT      (1 << 7)
#define USGFAULTACT    (1 << 3)
#define BUSFAULTACT    (1 << 1)
#define MEMFAULTACT    (1 << 0)

#endif
