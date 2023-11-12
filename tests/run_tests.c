#include "cpu_tests.c"
#include "../src/cpu/cpu.c"
#include "../src/cpu/memory_map.c"
int main(void) {
    cpu_load_rom_bytes();
    cpu_run_inc();
    cpu_jsr_test();
}
