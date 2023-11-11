#pragma once
#include <stdint.h>

// add the value of a certain register with the operand. Needed for certain opcodes.
#define ABSOLUTE_INDEXED(_opperand, _register) cpu->registers._register + _opperand;


struct registers {
    // the accumalator register
    uint8_t A;

    // the index register
    uint8_t X;
    uint8_t Y;

    // the program counter register
    unsigned short PC;

    // the stack pointer
    uint8_t SP;

    // the processor status register
    uint8_t PS;
};

typedef enum {
    ps_carry = 1 << 0x0,
    ps_zero = 1 << 0x1,
    ps_interrupt = 1 << 0x2,
    ps_decimalMode = 1 << 0x3,
    ps_breakCommand = 1 << 0x4,
    // status bit number 5 is unused
    ps_overflow = 1 << 0x6,
    ps_negative = 1 << 0x7,
} processor_status;
