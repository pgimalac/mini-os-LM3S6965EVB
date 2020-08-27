#include "systick.h"

uint32_t systick_tick;

void systick_init(uint32_t time) {
    systick_tick = 0;

    SYSTICK_RELOAD_ADDR = time & SYSTICK_RELOAD_MASK;
    SYSTICK_CTRL_ADDR |=
        SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_INT_ENABLE | SYSTICK_CTRL_CLOCK;
}
