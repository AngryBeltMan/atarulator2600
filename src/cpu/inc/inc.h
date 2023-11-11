#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "../cpu.h"
#include "../opcodes.h"
#include "../addressing.h"
static inline void opcodeInc(enum mem_addressing_mode mode,cpu6507 *cpu) {
    // the memory address that will be incremented;
    // gets the first opperand because all of the inc opcodes take atleast one byte opperand
    unsigned short address = parseOpperand(mode, cpu);
    // increment the memory value
    ++cpu->mem_map[address];
    // opcode INC only affects two flags: the negative flag if the 7th bit is on or if the result of incrementing the memory value is zero (wrapping around)
    set_flag(cpu, cpu->mem_map[address] >> 7, ps_negative);
    set_flag(cpu, cpu->mem_map[address] == 0, ps_zero);
}
// all of the INC opcode and its variations *
#define INC_CASES() \
    case 0xEE: \
        opcode.mode = Absolute; \
        opcode.opcode = INC; \
        break; \
    case 0xE6: \
        opcode.mode = ZeroPage; \
        opcode.opcode = INC; \
        break; \
    case 0xF6: \
        opcode.mode = XIndexedZeroPage; \
        opcode.opcode = INC; \
        break; \
    case 0xFE: \
        opcode.mode = XIndexedAbsolute; \
        opcode.opcode = INC; \
        break;
