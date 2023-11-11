#pragma once

/* #include <stdlib.h> */
/* #include <stdio.h> */

#include "../cpu.h"
#include "../opcodes.h"
// takes the @register_value argument and replaces it at the opperand value in the cpu's memory map
static void setRegister(enum mem_addressing_mode mode, cpu6507 *cpu, uint8_t *register_value);
