#ifndef ATARI_CPU
#define ATARI_CPU
#include "memory_map.h"
#include "registers.h"
// around 1.19 mhz
#define CLOCK_SPEED 1193182


typedef struct {
    // the atari 2600 memory map
    memory mem_map;
    // all of the cpu's registers
    struct registers registers;
    // the number of cycles an instruction took so we can caluclate ho long to sleep for before executing the next instruction
    uint8_t cycles_run;
    // TODO add tia
} cpu6507;

// sets the status flag bit to 1 or on in the comparison is true while setting it to zero if the comparison is false
static inline void set_flag(cpu6507 *cpu,int comparison, processor_status flag ) {
     cpu->registers.PS += ((cpu->registers.PS & flag) > 0 ? -(!comparison) : comparison) * flag;
}

void parseRom(cpu6507 *cpu);

// inits the cpu with the memory map filled with zeros and the registers set at its default values
cpu6507 initCpu();

// deallocs cpu's memory map
void freeCpu(cpu6507 cpu);

#endif
