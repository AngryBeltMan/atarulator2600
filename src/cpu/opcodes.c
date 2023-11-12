#include <assert.h>
#include "addressing.h"
#include "opcodes.h"
#include "inc/dec.h"
#include "memory_map.h"
#include "cpu.h"
#include "inc/inc.h"
#include "load/load.h"
#include "load/load.c"
#include "load/store.h"
#include "load/store.c"

#include "load/sta.h"
#include "load/stx.h"
#include "load/sty.h"
#include "load/lda.h"

#include "registers.h"
#include "trans/trans_opcodes.h"
#include "trans/trans_opcodes.c"

#include "stack/stack_opp.h"
#include "stack/stack_opp.c"
#include "stack/push_opcodes.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OPCODE_CASE(byte, _addressing_mode, opcode_name) \
    case byte: \
    opcode.mode = _addressing_mode; \
    opcode.opcode = opcode_name; \
    break;

// mutate a cpu register like adding and subtraction
#define MUT_REG(_opcode, _register, _opp)  \
    case _opcode: \
        cpu->registers._register += _opp; \
        cpu->cycles_run += 2; \
        set_flag(cpu, cpu->registers._register >> 7, ps_negative); \
        set_flag(cpu, cpu->registers._register == 0, ps_zero); \
        break;

opcode_info parseOpcode(cpu6507 *cpu) {
    opcode_info opcode;
    unsigned short pc = cpu->registers.PC;
    // cartridge min is the index where the rom starts.
    // code holds the current opcode being parsed
    uint8_t code = cpu->mem_map[pc];

    switch (code) {
        INC_CASES()
        STA_CASES()
        LDA_CASES()
        STX_CASES()
        STY_CASES()
        OPCODE_CASE(0xE8, Implied, INX)
        OPCODE_CASE(0xC8, Implied, INY)

        OPCODE_CASE(0xAA, Implied, TAX)
        OPCODE_CASE(0xA8, Implied, TAY)
        OPCODE_CASE(0xBA, Implied, TSX)
        OPCODE_CASE(0x8A, Implied, TXA)

        // opcodes that turn on a specific bit in the processor status register
        OPCODE_CASE(0x38, Implied, SEC)
        OPCODE_CASE(0xF8, Implied, SED)
        OPCODE_CASE(0x78, Implied, SEI)

        //stack opperation opcodes
        OPCODE_CASE(0x48, Implied, PHA)
        OPCODE_CASE(0x08, Implied, PHP)
        OPCODE_CASE(0x68, Implied, PLA)
        OPCODE_CASE(0x28, Implied, PLP)
        // no opperation opcode. puts the cpu on idle for two cycles
        OPCODE_CASE(0xEA, Implied, NOP)
        // jump statements manipulate the program counter register
        OPCODE_CASE(0x4C, Absolute, JMP)
        OPCODE_CASE(0x6C, AbsoluteIndirect, JMP)
        OPCODE_CASE(0x20, Absolute, JSR)
        OPCODE_CASE(0x60, Implied, RTS)

        // bitwise oppcodes
        OPCODE_CASE(0x0A, Accumalator, ASL_A)
        OPCODE_CASE(0x0E, Absolute, ASL)
        OPCODE_CASE(0x1E, XIndexedAbsolute, ASL)
        OPCODE_CASE(0x06, ZeroPage, ASL)
        OPCODE_CASE(0x16, XIndexedZeroPage, ASL)
        OPCODE_CASE(0x4A, Accumalator, LSR_A)
        OPCODE_CASE(0x4E, Absolute, LSR)
        OPCODE_CASE(0x5E, XIndexedAbsolute, LSR)
        OPCODE_CASE(0x46, ZeroPage, LSR)
        OPCODE_CASE(0x56, XIndexedZeroPage, LSR)

        default: {
            fprintf(stderr, "unknown opcode %i\n", code);
            abort();
            break;
         }
    };
    return opcode;
}

void executeOpcode(opcode_info opcode, cpu6507 *cpu) {
    switch (opcode.opcode) {
        case INC:
            opcodeInc(opcode.mode, cpu);
            break;
        case DEC:
            opcodeDec(opcode.mode, cpu);
            break;
        case STA: setMemory(opcode.mode, cpu, cpu->registers.A); break;
        case STX: setMemory(opcode.mode, cpu, cpu->registers.X); break;
        case STY: setMemory(opcode.mode, cpu, cpu->registers.Y); break;
        case LDA:
            // A register because this opcode mean LoaD Accumatlator (register)
            setRegister(opcode.mode, cpu, &cpu->registers.A);
            set_flag(cpu, cpu->registers.A >> 7, ps_negative);
            set_flag(cpu, cpu->registers.A == 0, ps_zero);
            break;
        case LDX:
            // A register because this opcode mean LoaD X (register)
            setRegister(opcode.mode, cpu, &cpu->registers.X);
            set_flag(cpu, cpu->registers.X >> 7, ps_negative);
            set_flag(cpu, cpu->registers.X == 0, ps_zero);
            break;
        case LDY:
            // A register because this opcode mean LoaD X (register)
            setRegister(opcode.mode, cpu, &cpu->registers.Y);
            set_flag(cpu, cpu->registers.Y >> 7, ps_negative);
            set_flag(cpu, cpu->registers.Y == 0, ps_zero);
            break;
        // 1 for the second argument so that the "comparison" is always true and therefore this flag bit should be garenteed to be set to one
        case SEC: set_flag(cpu, 1, ps_carry); break;
        case SED: set_flag(cpu, 1, ps_decimalMode); break;
        case SEI: set_flag(cpu, 1, ps_interrupt); break;

        case NOP: cpu->cycles_run += 2; break;
        case JMP: {
            unsigned short address = parseOpperand(opcode.mode, cpu);
            cpu->registers.PC = address;
            // return early because we want to skip the add one at the end of this function or else it would make it so we would get the opcode after the jump statement and not the current one
            return;
        }
        case JSR:
            // plus two because once we return back to this pc we would want to be at the next opcode and not at this opcode because it would cause an infinite loop
            // and adding two will get past the two bytes for the opperand
            cpu->registers.PC += 2;
            // push the lower bytes of the PC register onto the stack
            stack_push(cpu, cpu->registers.PC & 0xFF );

            // next push the upper bytes of the PC register onto the stack
            stack_push(cpu, (cpu->registers.PC & 0xFF00) >> 8 );
            // the new position when the cpu will jump to
            // opperand mode will always be absolute just calling this function to reduce the amount of code
            cpu->registers.PC -= 2;
            cpu->registers.PC = parseOpperand(opcode.mode, cpu);
            // return early because we want to skip the add one at the end of this function or else it would make it so we would get the opcode after the jump statement and not the current one
            return;
        case RTS: {
            // add the upper byte first because we push the upper bytes last and the last item pushed will be returned from a pop
            // combine the upper and lower bytes to get our original pc value before jumping via the JSR opcode
            cpu->registers.PC = stack_pop(cpu) << 8;
            cpu->registers.PC += stack_pop(cpu);
            cpu->cycles_run += 6;
            break;
        }
        case ASL_A: {
            // store the 7th bit that will be "pushed out" into the carry flag bit
            set_flag(cpu, cpu->registers.A << 7, ps_carry);
            cpu->registers.A <<= 1;
            set_flag(cpu, cpu->registers.A == 0, ps_zero);
            set_flag(cpu, cpu->registers.A << 7, ps_negative);
            break;
        }
        case ASL: {
            unsigned short address = parseOpperand(opcode.mode, cpu);
            // store the 7th bit that will be "pushed out" into the carry flag bit
            set_flag(cpu, cpu->mem_map[address] << 7, ps_carry);
            cpu->mem_map[address] <<= 1;
            set_flag(cpu, cpu->mem_map[address] == 0, ps_zero);
            set_flag(cpu, cpu->mem_map[address] << 7, ps_negative);
            break;
        }
        case LSR_A: {
            set_flag(cpu, cpu->registers.A & 0x1, ps_carry);
            cpu->registers.A >>= 1;
            set_flag(cpu, cpu->registers.A == 0, ps_zero);
            set_flag(cpu, 0, ps_negative);
            break;
        }
        case LSR: {
            unsigned short address = parseOpperand(opcode.mode, cpu);
            set_flag(cpu, cpu->mem_map[address] & 0x1, ps_carry);
            cpu->mem_map[address] >>= 1;
            set_flag(cpu, cpu->mem_map[address] == 0, ps_zero);
            // will always set the negative flag to zero because even if the 7th bit is on it will just be pushed down
            // Before left shift:
            // 10000000
            // ^ 7th bit (negative bit) on
            // After right shift:
            // 01000000
            // ^ 7th bit (negative bit) off
            set_flag(cpu, 0, ps_negative);
            break;
        }
        STACK_OPCODES()
        // Simple opcodes that just increment or decremnt certain registers.
        // These opcodes only have 1 addressing mode, do similar things, and take the same amount of cycles making them easily "macro-ized"
        MUT_REG(INX, X, 1)
        MUT_REG(INY, Y, 1)
        MUT_REG(DEX, X, -1)
        MUT_REG(DEY, Y, -1)
        // Contains all of the transfer _ register value to _ register.
        // All of them are stored in this macro because they all share
        // a common functionality and it keeps the opcodes.c file smaller.
        // The macro can be found in trans/trans_opcodes.h
        TRANS_OPCODE_CASES()
        default:
            fprintf(stderr, "uninitilized opcode %i", opcode.opcode);
            break;
    }
    // add one to get to the next instruction
    ++cpu->registers.PC;
}
