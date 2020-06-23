#include <stdint.h>

#include "irq.h"
#include "handlers.h"
#include "periphs/uart.h"

#define VTOR       (*(volatile uint32_t *) 0xE000ED08)
#define NVIC_ISER  (*(volatile uint32_t *) 0xE000E100)
#define NVIC_ICER  (*(volatile uint32_t *) 0xE000E180)
#define NVIC_ISPR  (*(volatile uint32_t *) 0xE000E200)
#define NVIC_ICPR  (*(volatile uint32_t *) 0xE000E280)

/* IRQ vectors table */
extern uint32_t *_stack;
extern void _start(void);

void *vector_table[] __attribute__ ((section(".vectors"))) = {
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    _start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    MemoryManagement_Handler, /* Memory Management Handler */
    BusFault_Handler,         /* Bus Fault handler */
    UsageFault_Handler,       /* Usage Fault Handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    DebugMonitor_Handler, /* Debug Monitor handler */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // External interrupts
    GPIOA_IRQHandler,
    GPIOB_IRQHandler,
    GPIOC_IRQHandler,
    GPIOD_IRQHandler,
    GPIOE_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    SSI0_IRQHandler,
    I2C0_IRQHandler,
    PWMFault_IRQHandler,
    PWMGen0_IRQHandler,
    PWMGen1_IRQHandler,
    PWMGen2_IRQHandler,
    QEI0_IRQHandler,
    ADC0Seq0_IRQHandler,
    ADC0Seq1_IRQHandler,
    ADC0Seq2_IRQHandler,
    ADC0Seq3_IRQHandler,
    WDTimer0_IRQHandler,
    Timer0A_IRQHandler,
    Timer0B_IRQHandler,
    Timer1A_IRQHandler,
    Timer1B_IRQHandler,
    Timer2A_IRQHandler,
    Timer2B_IRQHandler,
    AnalogCmp0_IRQHandler,
    AnalogCmp1_IRQHandler,
    0,
    SC_IRQHandler,
    FMC_IRQHandler,
    GPIOF_IRQHandler,
    GPIOG_IRQHandler,
    0,
    UART2_IRQHandler,
    0,
    Timer3A_IRQHandler,
    Timer3B_IRQHandler,
    I2C1_IRQHandler,
    QEI1_IRQHandler,
    0,
    0,
    0,
    Ethernet_IRQHandler,
    Hibernation_IRQHandler
};

extern char _irq_table;

void irq_init()
{
    // Relocate VTOR table
    VTOR = (uint32_t) &_irq_table;
}

void irq_enable(int irq_number)
{
    NVIC_ISER |= (1 << irq_number);
}

void irq_disable(int irq_number)
{
    NVIC_ICER |= (1 << irq_number);
}
