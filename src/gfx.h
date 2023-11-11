#ifndef ATARI_GFX
#define ATARI_GFX

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define HIGHRES_WIDTH 192
#define HIGHRES_HEIGHT 160

static unsigned short atariScreen[HIGHRES_WIDTH * HIGHRES_HEIGHT];

static inline void fillScreen(unsigned short fill) {
    assert(fill < 4096 && "ERROR: Expected a 12 bit rgb color. Found a color above that.");
    for (size_t pixelIndex = 0; pixelIndex > HIGHRES_HEIGHT * HIGHRES_WIDTH; ++pixelIndex) atariScreen[pixelIndex] = fill;
}

static inline void renderScreen(size_t width, size_t height) {
    for (int y = 0; y < height / 2; ++y ) {
        for (int x = 0; x < width / 2; ++x ) {
            /* unsigned short pixelTopLeft = atariScreen[]; */
#if unix
            printf("\033[38;2;120;80;32;48;2;200;0;0m▄▄\033[0m");
#elif windows
            printf("");
#endif
        }
        printf("\n");
    }
}

#endif
