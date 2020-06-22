#include <stdint.h>
#include <stddef.h>

#include "irq/irq.h"
#include "periphs/systick.h"
#include "periphs/uart.h"

int main()
{
  enable_irq();

  systick_init(0xFFFFF);

  uart0_write("A");

  while (1) {}

  return 0;
}
