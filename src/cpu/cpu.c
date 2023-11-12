#include "cpu.h"
#include "memory_map.h"
#include "opcodes.h"
#include "opcodes.c"
#include <stdint.h>
void parseRom(cpu6507 *cpu) {
    uint8_t opcode;
    while (1) {
        opcode = cpu->mem_map[cpu->registers.PC];
        // if it encounter the break opcode just exit for right now
        if (opcode == 0x0) return;
        // get information about the opcode like its memory mode the opcode type
        opcode_info opcode_data = parseOpcode(cpu);
        executeOpcode(opcode_data, cpu);
    }
}

cpu6507 initCpu() {
    cpu6507 cpu;
    // this is where the program in rom starts
    cpu.registers.PC = CARTRIDGE_MIN;
    // 128 is the default value because this is the stack register and the stack register expands downwards
    cpu.registers.SP = 0x80;
    cpu.registers.A = 0x0;
    cpu.registers.X = 0x0;
    cpu.registers.Y = 0x0;
    // when the cpu starts there a no processor status flags
    cpu.registers.PS = 0x0;

    cpu.cycles_run = 0x0;
    // just mallocs 2^13 or 8 kb which is how big the 6507 cpu's memory map is
    // after it mallocs it all of the values are set to 0
    cpu.mem_map = memory_map_new();
    return cpu;
}

void freeCpu(cpu6507 cpu) {
    // deallocate the memory map
    free(cpu.mem_map);
}
