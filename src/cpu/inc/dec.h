#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "../cpu.h"
#include "../opcodes.h"
#include "../addressing.h"
static inline void opcodeDec(enum mem_addressing_mode mode,cpu6507 *cpu) {
    // the memory address that will be incremented;
    // gets the first opperand because all of the inc opcodes take atleast one byte opperand
    unsigned short address = parseOpperand(mode, cpu);
    // increment the memory value
    --cpu->mem_map[address];

    // opcode INC only affects two flags: the negative flag if the 7th bit is on or if the result of incrementing the memory value is zero (wrapping around)
    set_flag(cpu, cpu->mem_map[address] >> 7, ps_negative);
    set_flag(cpu, cpu->mem_map[address] == 0, ps_zero);
}
// all of the INC opcode and its variations *
#define DEC_CASES() \
    case 0xCE: \
        opcode.mode = Absolute; \
        opcode.opcode = DEC; \
        break; \
    case 0xE6: \
        opcode.mode = ZeroPage; \
        opcode.opcode = DEC; \
        break; \
    case 0xD6: \
        opcode.mode = XIndexedZeroPage; \
        opcode.opcode = DEC; \
        break; \
    case 0xDE: \
        opcode.mode = XIndexedAbsolute; \
        opcode.opcode = DEC; \
        break;
