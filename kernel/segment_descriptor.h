#ifndef SEGMENT_DESCRIPTOR_H_INCLUDED
#define SEGMENT_DESCRIPTOR_H_INCLUDED

#include <stdint.h>

// see 3.4.5.1 Code- and Data-Segment Descriptor Types - Intel 64 and IA-32
// Architectures Software Developer's Manual, Volume 3
#define SEG_ACCESSED     0b0001
// all data segments are readable
#define SEG_DATA_READ    0b0000 // for data segments with no other flags set
#define SEG_DATA_WRITE   0b0010
#define SEG_DATA_EXPAND  0b0100
// all code segments are executable
#define SEG_CODE_EXECUTE 0b1000 // for code segments with no other flags set
#define SEG_CODE_READ    0b1010
#define SEG_CODE_CONFORM 0b1100

// see 3.4.5 Segment Descriptors - Intel SDM, Volume 3
typedef union __attribute__((packed)) seg_descriptor_properties {
    uint16_t data;
    struct {
        // interpretation depends on desc_type.
        // for a code/data segment (desc_type=1), see SEG_* macros above
        uint8_t seg_type    : 4;
        // set for a code or data segment, clear for a system segment
        uint8_t desc_type   : 1;
        // 0 to 3, in order of decreasing privilege
        uint8_t priv_lvl    : 2;
        // set if segment is present in memory, clear otherwise
        uint8_t seg_present : 1;
        uint8_t             : 4; // skipped. overlap with 4 bits of segment limit
        uint8_t             : 1; // available for system use. unused
        uint8_t             : 1; // must be clear when not in IA-32e mode
        // for code and data segments, set for 32-bit
        // set for 32-bit code/data segments. clear for 16-bit code/data segments.
        // for an expand-down data segment, set for FFFFFFFF upper bound, or clear
        // for FFFF upper bound.
        uint8_t big         : 1;
        // set if limit is in 4KB page units, clear for byte units.
        uint8_t granularity : 1;
    };
} seg_descriptor_properties_t;

typedef struct __attribute__((packed)) pseudo_descriptor {
    uint16_t limit;
    uint32_t base;
} pseudo_descriptor_t;

uint64_t make_seg_descriptor(uint32_t base, uint32_t limit, union seg_descriptor_properties properties);

#endif // ifndef SEGMENT_DESCRIPTOR_H_INCLUDED
