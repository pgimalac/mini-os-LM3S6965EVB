#include <stdint.h>
#include <stddef.h>
#include "irq.h"

#define UART0DR (*(volatile uint32_t *) 0x4000C000)

int main()
{
  enable_irq();

  UART0DR = (uint32_t) 'A';

  while (1) {}

  return 0;
}
