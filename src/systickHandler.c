#include <stdint.h>
#include "pendSV.h"
#define STRELOAD (*(volatile uint32_t*) 0xE000E014)
#define STCTRL (*(volatile uint32_t*) 0xE000E010)

void systickException(void){
    STCTRL = STCTRL | 0b111;
    STRELOAD =0x00FFFFFF;
}
