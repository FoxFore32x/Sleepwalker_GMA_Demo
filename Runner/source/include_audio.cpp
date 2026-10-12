#include "include_audio.h"

#if defined(__gamecube__) || defined(__wii__)
const uint8_t *ogg_refs[] = {
_0_ogg,
_1_ogg
};

const size_t ogg_refs_size[] = {
_0_ogg_size,
_1_ogg_size
};



#endif

#if defined(raylib)
    const char *ogg_refs[] = {
    "0.ogg",
    "1.ogg"
    };
#endif