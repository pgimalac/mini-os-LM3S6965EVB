#include "irq/handlers.h"
#include "irq/irq.h"
#include "periphs/uart.h"

#define MAKE_DEFAULT_HANDLER(x)                                                \
    void __attribute__((weak)) x(void) {                                       \
        disable_irq();                                                         \
        uart0_write(#x);                                                       \
        uart0_write(" default\n");                                             \
        while (1)                                                              \
            ;                                                                  \
    }

MAKE_DEFAULT_HANDLER(NMI_Handler)
MAKE_DEFAULT_HANDLER(HardFault_Handler)
MAKE_DEFAULT_HANDLER(MemoryManagement_Handler)
MAKE_DEFAULT_HANDLER(BusFault_Handler)
MAKE_DEFAULT_HANDLER(UsageFault_Handler)
MAKE_DEFAULT_HANDLER(SVC_Handler)
MAKE_DEFAULT_HANDLER(DebugMonitor_Handler)
MAKE_DEFAULT_HANDLER(PendSV_Handler)
MAKE_DEFAULT_HANDLER(SysTick_Handler)
MAKE_DEFAULT_HANDLER(GPIOA_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOB_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOC_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOD_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOE_IRQHandler)
MAKE_DEFAULT_HANDLER(UART0_IRQHandler)
MAKE_DEFAULT_HANDLER(UART1_IRQHandler)
MAKE_DEFAULT_HANDLER(SSI0_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C0_IRQHandler)
MAKE_DEFAULT_HANDLER(PWMFault_IRQHandler)
MAKE_DEFAULT_HANDLER(PWMGen0_IRQHandler)
MAKE_DEFAULT_HANDLER(PWMGen1_IRQHandler)
MAKE_DEFAULT_HANDLER(PWMGen2_IRQHandler)
MAKE_DEFAULT_HANDLER(QEI0_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC0Seq0_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC0Seq1_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC0Seq2_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC0Seq3_IRQHandler)
MAKE_DEFAULT_HANDLER(WDTimer0_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer0A_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer0B_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer1A_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer1B_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer2A_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer2B_IRQHandler)
MAKE_DEFAULT_HANDLER(AnalogCmp0_IRQHandler)
MAKE_DEFAULT_HANDLER(AnalogCmp1_IRQHandler)
MAKE_DEFAULT_HANDLER(SC_IRQHandler)
MAKE_DEFAULT_HANDLER(FMC_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOF_IRQHandler)
MAKE_DEFAULT_HANDLER(GPIOG_IRQHandler)
MAKE_DEFAULT_HANDLER(UART2_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer3A_IRQHandler)
MAKE_DEFAULT_HANDLER(Timer3B_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_IRQHandler)
MAKE_DEFAULT_HANDLER(QEI1_IRQHandler)
MAKE_DEFAULT_HANDLER(Ethernet_IRQHandler)
MAKE_DEFAULT_HANDLER(Hibernation_IRQHandler)
