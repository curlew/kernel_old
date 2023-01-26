#include "gdt.h"

.section .text
.global reload_segment_regs
.type reload_segment_regs, @function
reload_segment_regs:
    /* far jump into code segment to reload CS register */
    jmp $GDT_CS_SELECTOR, $1f

1:
    /* manually reload other segment registers */
    movw $GDT_DS_SELECTOR, %ax
    movw %ax, %ds
    movw %ax, %ss
    movw $0, %ax
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    ret
