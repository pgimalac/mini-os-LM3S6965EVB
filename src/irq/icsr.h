#ifndef ICSR_H
#define ICSR_H

#include <stdint.h>

/* INTERRUPT CONTROL STATE REGISTER */

// https://developer.arm.com/docs/ddi0337/e/nested-vectored-interrupt-controller/nvic-programmers-model/nvic-register-descriptions

#define ICSR_ADDR (*(volatile uint32_t *)0xE000ED04)

#define NMIPENDSET (1 << 31)

#define PENDSVSET (1 << 28)
#define PENDSVCLR (1 << 27)

#define PENDSTSET (1 << 26)
#define PENDSTCLR (1 << 25)

#define ISRPREEMPT (1 << 24)
#define ISRPENDING (1 << 23)

void trigger_pendsv();
void clear_pendsv();

void trigger_sysclick();
void clear_sysclick();

#endif
