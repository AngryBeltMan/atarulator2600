#include "stack_opp.h"
#include "../memory_map.h"
void stack_push(cpu6507 *cpu, uint8_t value) {
    // decrement the stack pointer and push/overwrite the new value to that memory location
    cpu->mem_map[RAM_MIN + (--cpu->registers.SP) ] = value;
}
uint8_t stack_pop(cpu6507 *cpu) {
    ++cpu->registers.SP;
    // minus one because we previously incremented the stack pointer and we need to return it back to the previous value so we can return the current stack element
    return cpu->mem_map[RAM_MIN + (cpu->registers.SP - 1)];
}
