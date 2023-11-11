#include "../src/cpu/cpu.h"
#include "../src/cpu/rom.h"
#include "t_assert.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cpu_load_rom_bytes() {
    cpu6507 cpu = initCpu();
    uint8_t *prgm = malloc(5);
    memset(prgm, 0x1, 5);
    load_rom_bytes(prgm, 5, &cpu);

    ASSERT(cpu.mem_map[CARTRIDGE_MIN] == 0x1);
    ASSERT(cpu.mem_map[CARTRIDGE_MIN + 1] == 0x1);
    ASSERT(cpu.mem_map[CARTRIDGE_MIN + 2] == 0x1);
    ASSERT(cpu.mem_map[CARTRIDGE_MIN + 3] == 0x1);
    ASSERT(cpu.mem_map[CARTRIDGE_MIN + 4] == 0x1);
    ASSERT(cpu.mem_map[CARTRIDGE_MIN + 5] == 0x0);
    freeCpu(cpu);
}

void cpu_run_inc() {
    cpu6507 cpu = initCpu();
    uint8_t *prgm = malloc(4);
    // increment memory address 0x1
    prgm[0] = 0xE6;
    prgm[1] = 0x1;
    // store the the value at 0x1 into register A
    prgm[2] = 0xA5;
    prgm[3] = 0x1;

    load_rom_bytes(prgm, 4, &cpu);
    parseRom(&cpu);
    ASSERT(cpu.mem_map[1] == 1)
    ASSERT(cpu.registers.PC == 4)
    ASSERT(cpu.registers.A == 1)
    ASSERT(cpu.registers.PS == 0)
    freeCpu(cpu);
}
