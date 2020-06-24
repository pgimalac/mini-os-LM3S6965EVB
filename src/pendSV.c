#include <stdint.h>
#define ICSR (*(volatile uint32_t*)0xE000ED04)

void pendSVException(void){
    ICSR |= 1<<28;
}