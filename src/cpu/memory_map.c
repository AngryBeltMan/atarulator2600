#ifndef MEM_MAP_IMPL
#define MEM_MAP_IMPL
#include "memory_map.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

memory memory_map_new() {
    // 8 kilobytes because that is how big the memory map for the atari 2600 is
    memory mem_map = malloc((1 << 13) - 1);
    // set all of the bytes to zero
    memset(mem_map, 0, (1 << 13) - 1);
    return mem_map;
}

void memory_free(memory* mem_map) {
    free(*mem_map);
    *mem_map = NULL;
}
#endif
