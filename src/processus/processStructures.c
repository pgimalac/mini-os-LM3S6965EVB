#include <stdint.h>

struct process{
    uint32_t flag;
    uint32_t pid;
    uint32_t* stack;
    
};
struct hw_context {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t ip;
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;

};
struct sw_context {
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t v4;
    uint32_t v5;
    uint32_t v6;
    uint32_t v7;
    uint32_t v8;
};
