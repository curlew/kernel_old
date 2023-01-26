.set STACK_SIZE, 0x4000 /* 16 KiB */

.section .stack, "aw", @nobits
.align 16
stack_bottom:
.skip STACK_SIZE
stack_top:


.section .text
.global _start
.type _start, @function
_start:
    /* https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Machine-state

       - EAX contains 0x2BADB002 (MULTIBOOT_BOOTLOADER_MAGIC)
       - EBX contains the physical address of the multiboot info struct
       - ESP, GDTR, and IDTR are undefined
       - processor is in protected mode, paging is disabled
       - the A20 gate is enabled
     */

    cli
    movl $stack_top, %esp

    pushl %ebx /* multiboot information struct */
    pushl %eax /* multiboot bootloader magic */
    call init

halt:
    hlt
    jmp halt

.size _start, . - _start
