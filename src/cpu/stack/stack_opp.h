// contains all of the stack opperations
#pragma once
#include <stdint.h>
#include "../cpu.h"
// decrements the stack pointer and puts the argument "value" into that stack location
void stack_push(cpu6507 *cpu, uint8_t value);

// increments the stack pointer and returns the value previously at that stack pointer location
uint8_t stack_pop(cpu6507 *cpu);

#define STACK_OPCODES() \
    case PHP: \
        stack_push(cpu, cpu->registers.PS); \
        cpu->cycles_run += 3; \
        break; \
    case PHA: \
        stack_push(cpu, cpu->registers.A); \
        cpu->cycles_run += 3; \
        break; \
    case PLA: \
        cpu->registers.A =  stack_pop(cpu); \
        set_flag(cpu, cpu->registers.A >> 7, ps_negative); \
        set_flag(cpu, cpu->registers.A == 0, ps_zero); \
        cpu->cycles_run += 4; \
        break; \
    case PLP: \
        cpu->registers.PS = stack_pop(cpu); \
        cpu->cycles_run += 4; \
        break;
