#ifndef UART_H
#define UART_H

#define UART0_ADDR (*(volatile uint32_t *) 0x4000C000)

int uart0_write(char *);
void uart0_write_int(int);

#endif
