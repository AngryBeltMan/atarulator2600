#ifndef MEM_MAP
#define MEM_MAP
#include <stdint.h>
#include <stdlib.h>

// these define the sections in the memory map
#define TIA_REG_MIN 0x0
#define TIA_REG_MAX 0x7F

#define RAM_MIN 0x80
#define RAM_MAX 0xFF

#define RIOT_MIN 0x200
#define RIOT_MAX 0x2FF

#define CARTRIDGE_MIN 0x1000
#define CARTRIDGE_MAX 0x1FFF


typedef uint8_t *memory;

typedef struct {
    uint8_t *tia_write;
    uint8_t *tia_read;
    uint8_t *pia_ram;
    uint8_t *pia_io_timer;
    uint8_t *cartridge;
} memory_map;

memory memory_map_new();

void memory_free(memory* mem_map);

#endif
