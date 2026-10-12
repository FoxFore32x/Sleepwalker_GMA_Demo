#pragma once
#include <stddef.h>
#include <stdint.h>
#if defined(__gamecube__) || defined(__wii__)
#include <gccore.h>
#endif
#include "oggplayer.h"

#if defined(__gamecube__) || defined(__wii__)
extern const uint8_t *ogg_refs[];
extern const size_t ogg_refs_size[];


#include "0_ogg.h"
#include "1_ogg.h"
#endif

#if defined(raylib)
    extern const char *ogg_refs[];
#endif