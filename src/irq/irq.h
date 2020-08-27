#ifndef IRQ_H
#define IRQ_H

void irq_init(void);
void irq_enable(int irq_number);
void irq_disable(int irq_number);

#define enable_irq() asm volatile("cpsie i")
#define disable_irq() asm volatile("cpsid i")

#endif
