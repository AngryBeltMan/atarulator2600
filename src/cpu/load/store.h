#pragma once

#include "../cpu.h"
#include "../opcodes.h"
// gets the @register_value and sets it into the cpu's memory map given the addressing mode
static void setMemory(enum mem_addressing_mode mode, cpu6507 *cpu, uint8_t register_value);
