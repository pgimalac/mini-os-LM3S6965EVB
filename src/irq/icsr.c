#include "icsr.h"

void trigger_pendsv() {
    ICSR_ADDR |= PENDSVSET;
}

void clear_pendsv() {
    ICSR_ADDR |= PENDSVCLR;
}

void trigger_sysclick() {
    ICSR_ADDR |= PENDSTSET;
}

void clear_sysclick() {
    ICSR_ADDR |= PENDSTCLR;
}
