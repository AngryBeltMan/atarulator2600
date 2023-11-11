#pragma once
#include "../cpu.h"
#include "../opcodes.h"
#include <stdint.h>

void TransferRegister(cpu6507 *cpu, uint8_t *cpu_reg, uint8_t new_value);
// contains all of the transfer register opcodes and their function
#define TRANS_OPCODE_CASES() \
    case TAX: \
        TransferRegister(cpu, &cpu->registers.A, cpu->registers.X); \
        set_flag(cpu, cpu->registers.Y >> 7, ps_negative); \
        set_flag(cpu, cpu->registers.Y == 0, ps_zero); \
        break; \
    case TAY: \
        TransferRegister(cpu, &cpu->registers.Y, cpu->registers.A); \
        set_flag(cpu, cpu->registers.Y >> 7, ps_negative); \
        set_flag(cpu, cpu->registers.Y == 0, ps_zero); \
        break; \
    case TSX: \
        TransferRegister(cpu, &cpu->registers.X, cpu->registers.SP); \
        set_flag(cpu, cpu->registers.X >> 7, ps_negative); \
        set_flag(cpu, cpu->registers.X == 0, ps_zero); \
        break; \
    case TXA: \
        TransferRegister(cpu, &cpu->registers.X, cpu->registers.A); \
        set_flag(cpu, cpu->registers.A >> 7, ps_negative); \
        set_flag(cpu, cpu->registers.A == 0, ps_zero); \
        break; \
    case TXS: \
        TransferRegister(cpu, &cpu->registers.X, cpu->registers.SP); \
        /* no set flags because this is the only transfer opcode that doesn't change any flags */ \
        break;
