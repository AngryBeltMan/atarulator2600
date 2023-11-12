#pragma once
#include "cpu.h"

enum opcodes {
    // all of the inc opcodes
    // increments a given memory address value by one
    INC,
    // decrement a given memory address value by one
    DEC,
    // decrement the y register
    DEY,
    // increments the x register
    INX,
    // increments the y register
    INY,
    // decrement the x register
    DEX,
    // all of the load registers
    // stores the accumalator register (A) into a memory address
    STA,
    // stores the accumalator register (X) into a memory address
    STX,
    // stores the accumalator register (X) into a memory address
    STY,
    // loads a given value in memory into the A(ccumalator) register
    LDA,
    // loads a given value in memory into the X register
    LDX,
    // loads a given value in memory into the Y register
    LDY,
    // Transfer Accumaltor to X register
    TAX,
    // Transfer Accumaltor to Y register
    TAY,
    // Transfer Stack Register to X register
    TSX,
    // Transfer X Register to A(ccumaltor) register
    TXA,
    // Transfer X Register to Stack register
    TXS,
    // Transfer Y Register to A(ccumalator) register
    TYA,
    // sets the carry flag bit to one in the P(rocessor) S(tatus) register
    SEC,
    // sets the decimal flag bit to one in the P(rocessor) S(tatus) register
    SED,
    // sets the interrupt disabled flag bit to one in the P(rocessor) S(tatus) register
    SEI,
    // stands for NO OPeration and just increments the cycle count
    NOP,
    // pushes the accumalator register to the stack
    PHA,
    // pushes the processor status register to the stack
    PHP,
    // loads the accumaltor register from the stack popping the element from the stack
    PLA,
    // loads the Processor status from the stack popping the current element from the stack
    PLP,
    // loads the Processor status from the stack popping the current element from the stack
    JMP,
    // pushes the current pc register into the stack in little eadian order then sets the pc to the opperand value
    JSR,
    // return back from where the opcode JSR was called
    RTS,
    // ASL_A and ASL are the same opcode however ASL_A hase only one addressing mode that affects the Acculator register only.
    // And the ASL has many addressing modes. I split these opcodes because it is more convienient to implement
    // arithmetic shift left to the accumalator register
    ASL_A,
    // arithmetic shift left to a memory address
    ASL,
    // arithmetic shift right to a memory address
    LSR_A,
    LSR

};

enum mem_addressing_mode {
    Accumalator,
    Implied,
    Immediate,
    Absolute,
    ZeroPage,
    Relative,

    AbsoluteIndirect,

    XIndexedAbsolute,
    YIndexedAbsolute,

    XIndexedZeroPage,
    YIndexedZeroPage,

    XIndexZeroPageIndirect,
    YIndexZeroPageIndirect,
};
typedef struct {
    enum opcodes opcode;
    // all opcodes have a memory addressing mode
    enum mem_addressing_mode mode;

} opcode_info;

opcode_info parseOpcode(cpu6507 *cpu);

void executeOpcode(opcode_info opcode, cpu6507 *cpu );

