#include "multiboot.h"
#include "segment_descriptor.h"
#include "gdt.h"
#include "tty.h"
#include <stdalign.h>
#include <stdint.h>

void init(uint32_t boot_magic, struct multiboot_info *boot_info) {
    if (boot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }

    alignas(8) static uint64_t gdt[3];

    // null descriptor
    gdt[GDT_NULL_INDEX] = make_seg_descriptor(0, 0, (seg_descriptor_properties_t){0});

    // code segment
    gdt[GDT_CS_INDEX] = make_seg_descriptor(0, 0xFFFFFul, (seg_descriptor_properties_t){
        .seg_type    = SEG_CODE_READ,
        .desc_type   = 1,
        .priv_lvl    = 0,
        .seg_present = 1,
        .big         = 1,
        .granularity = 1,
    });

    // data segment
    gdt[GDT_DS_INDEX] = make_seg_descriptor(0, 0xFFFFFul, (seg_descriptor_properties_t){
        .seg_type    = SEG_DATA_WRITE,
        .desc_type   = 1,
        .priv_lvl    = 0,
        .seg_present = 1,
        .big         = 1,
        .granularity = 1,
    });

    pseudo_descriptor_t gdtr = {
        .limit = sizeof (gdt) - 1,
        .base = (uint32_t)&gdt
    };

    __asm__ volatile("lgdt %0" : : "m" (gdtr));
    reload_segment_regs();

    clear();
    puts("hello world");
}
