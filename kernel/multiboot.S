#define ASM_FILE
#include "multiboot.h"

/* align boot modules on 4KB page boundaries and provide memory information via
   multiboot information struct */
.set MULTIBOOT_HEADER_FLAGS, MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO

/* https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-layout */
.section .multiboot, "a"
.align 4 /* multiboot header must be 32-bit aligned */

.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

/* address fields. not required as kernel image is in ELF format */
.long 0 /* header_addr */
.long 0 /* load_addr */
.long 0 /* load_end_addr */
.long 0 /* bss_end_addr */
.long 0 /* entry_addr */

/* graphics fields, enabled by MULTIBOOT_VIDEO_MODE flag */
.long 0 /* mode_type */
.long 0 /* width */
.long 0 /* height */
.long 0 /* depth */
