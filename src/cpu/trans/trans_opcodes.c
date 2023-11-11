#include "trans_opcodes.h"
void TransferRegister(cpu6507 *cpu, uint8_t *cpu_reg, uint8_t new_value) {
    cpu->cycles_run += 2;
    *cpu_reg = new_value;
}
