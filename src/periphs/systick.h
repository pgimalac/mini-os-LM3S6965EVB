#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

/* SYSTICK */

// http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0179b/ar01s02s08.html
// https://developer.arm.com/docs/ddi0337/e/nested-vectored-interrupt-controller/nvic-programmers-model/nvic-register-descriptions

#define SYSTICK_CTRL_ADDR (*(volatile uint32_t *)0xE000E010)
#define SYSTICK_RELOAD_ADDR (*(volatile uint32_t *)0xE000E014)
#define SYSTICK_CURRENT_ADDR (*(volatile uint32_t *)0xE000E018)

#define SYSTICK_CTRL_MASK (((uint32_t)-1) << 3)
#define SYSTICK_CTRL_ENABLE (1 << 0)
#define SYSTICK_CTRL_INT_ENABLE (1 << 1)
#define SYSTICK_CTRL_CLOCK (1 << 2)

#define SYSTICK_RELOAD_MASK 0xFFFFFF
void systick_init(uint32_t);

extern uint32_t systick_tick;

#endif
