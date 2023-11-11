#include "store.h"
#include "../cpu.h"
#include "../opcodes.h"
#include "../addressing.h"

static inline void setMemory(enum mem_addressing_mode mode, cpu6507 *cpu, uint8_t register_value) {
    // the memory address that will be incremented;
    // gets the first opperand because all of the inc opcodes take atleast one byte opperand
    unsigned short address = parseOpperand(mode, cpu);
    // stores the register value into memory
    cpu->mem_map[address] = register_value;
}
