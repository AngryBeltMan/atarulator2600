#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cpu.h"
#include "memory_map.h"
static inline void load_rom(FILE* rom, cpu6507 *cpu ) {
    char romByte;
    // the index where the byte should go
    size_t rom_index = 0;
    // gets a rom byte while it doesn't encounter and End Of File (EOF) byte
    while ((romByte = fgetc(rom)) != EOF) {
        assert(rom_index < 4096 && "ERROR: current enumlator version does not support roms larger that 4 kilobytes");
        // CARTEIDGE_MIN is the index in the cpu's memory map where the start of the rom is located
        cpu->mem_map[CARTRIDGE_MIN + rom_index] = romByte;
    }
}

static inline void load_rom_bytes(uint8_t* rom_bytes,size_t rom_len, cpu6507 *cpu ) {
    // the index where the byte should go
    assert(rom_len < 4096 && "ERROR: current enumlator version does not support roms larger that 4 kilobytes");
    // gets a rom byte while it doesn't encounter and End Of File (EOF) byte
    /* while ((romByte = fgetc(rom)) != EOF) { } */
    for (size_t rom_index = 0; rom_index < rom_len; ++rom_index) {
        // CARTEIDGE_MIN is the index in the cpu's memory map where the start of the rom is located
        cpu->mem_map[CARTRIDGE_MIN + rom_index] = rom_bytes[rom_index];
    }
}
