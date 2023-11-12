#pragma once
#include "cpu.h"
#include "memory_map.h"
#include "opcodes.h"
#include <stdio.h>
// parses the opperands given the addressing mode
static inline unsigned short parseOpperand(enum mem_addressing_mode mode,cpu6507 *cpu) {
    // the memory address that will be incremented;
    // gets the first opperand because all of the inc opcodes take atleast one byte opperand
    // TODO: Refactor to make it less messy somehow keep increment the cycle count correctly
    unsigned short address = cpu->mem_map[++cpu->registers.PC];

    switch (mode) {
        // add the value in the x register to find the address to increment
        case XIndexedZeroPage:
            address = ABSOLUTE_INDEXED(address, X);
            break;
        case YIndexedZeroPage:
            address = ABSOLUTE_INDEXED(address, Y);
            break;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="
            // ignore the case statment fall through because it is intentional as the X and Y indexed version of the Absolute addressing is the exact same except we add the X or Y register offset.
            // So instead of repeating code we can just add the X or Y offset then fall through and run the absolute addressing mode.
        case YIndexedAbsolute:
        case XIndexedAbsolute:
            if (mode == XIndexedAbsolute) {
                address = ABSOLUTE_INDEXED(address, X);
            } else {
                address = ABSOLUTE_INDEXED(address, Y);
            }
            // add one because we will run case Absolute next which will add six making the cycle count 5 which is how much cycles XIndexedAbsolute takes
            ++cpu->cycles_run;
        case Absolute: {
            // add the second half of the memory
            address += cpu->mem_map[++cpu->registers.PC] << 8;
            break;
        }
#pragma GCC diagnostic pop
        case YIndexZeroPageIndirect:
        case XIndexZeroPageIndirect: {
            // adds the X or Y register into address which will "point to" the location in memory that is our desired memory address
            address += mode == XIndexZeroPageIndirect ? cpu->registers.X : cpu->registers.Y;
            // the low order of the bytes
            uint8_t low_byte = cpu->mem_map[address];
            // the high order of the bytes
            uint8_t high_byte = cpu->mem_map[address + 1];
            address = (high_byte << 8) + low_byte;
            break;
        }
        case AbsoluteIndirect: {
            address += cpu->mem_map[++cpu->registers.PC];
            uint8_t low_byte = cpu->mem_map[address];
            uint8_t high_byte = cpu->mem_map[address + 1];
            address = (high_byte << 8) + low_byte;
            break;
        }
        case Immediate:
            break;
        // zero page takes only one byte as a opperand as it can oly index the first 256 bytes of memory. which is why we don't need to mutate the var address anymore because we already
        case ZeroPage:
            break;
        default:
            fprintf(stderr, "unsupport addressing mode for opcode: %i", mode);
    }
    return address;
}
