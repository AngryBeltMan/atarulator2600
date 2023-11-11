#include "../cpu.h"
#include "../opcodes.h"
#include "load.h"
#include "../addressing.h"
static inline void setRegister(enum mem_addressing_mode mode, cpu6507 *cpu, uint8_t *register_value) {
    // the memory address that will be incremented;
    // gets the first opperand because all of the inc opcodes take atleast one byte opperand
    unsigned short address = parseOpperand(mode, cpu);
    // sets the given memory address to a certain register value
    *register_value = cpu->mem_map[address];
    // opcode INC only affects two flags: the negative flag if the 7th bit is on or if the result of incrementing the memory value is zero (wrapping around)
    set_flag(cpu, cpu->mem_map[address] >> 7, ps_negative);
    set_flag(cpu, cpu->mem_map[address] == 0, ps_zero);
}
