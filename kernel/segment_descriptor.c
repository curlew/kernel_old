#include "segment_descriptor.h"

_Static_assert(sizeof (union seg_descriptor_properties) == 2);

uint64_t make_seg_descriptor(uint32_t base, uint32_t limit, union seg_descriptor_properties properties) {
    uint64_t desc = 0;

    // segment limit 15:0 -> descriptor 15:0
    desc |= limit & 0x0000FFFFull;
    // segment limit 19:16 -> descriptor 51:48
    desc |= (limit & 0x000F0000ull) << (48 - 16); // 48-16: start at 48, 0000FFFF is 16 bits

    // base 23:0 -> descriptor 39:16
    desc |= (base & 0x00FFFFFFull) << 16;
    // base 31:24 -> descriptor 63:56
    desc |= (base & 0xFF000000ull) << (56 - 24); // 56-24: start at 56, 00FFFFFF is 24 bits

    // properties 7:0 -> descriptor 47:40
    // -- skip 4 bits of segment limit --
    // properties 15:12 -> descriptor 55:52
    desc |= (properties.data & 0x0000F0FFull) << 40;

    return desc;
}
