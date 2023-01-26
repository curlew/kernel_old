SRC = kernel/boot.S kernel/multiboot.S kernel/init.c kernel/segment_descriptor.c kernel/gdt.S kernel/tty.c kernel/vga.c

CC 	     = i686-elf-gcc
CFLAGS   = -Wall -Wextra -Wshadow -Og -g -ffreestanding -std=c17
CPPFLAGS = -MMD -MP
LDFLAGS  = -nostdlib -T kernel/linker.ld
LDLIBS   = -lgcc

OBJ := $(SRC:%=build/%.o)
DEPS := $(OBJ:.o=.d)

.PHONY: all qemu clean

all: build/kernel.iso

qemu: build/kernel.iso
	qemu-system-x86_64 -serial stdio $<

clean:
	-rm -r build

build/kernel.iso: build/kernel.bin kernel/grub.cfg
	mkdir -p build/iso/boot/grub
	cp kernel/grub.cfg build/iso/boot/grub
	cp build/kernel.bin build/iso/boot
	grub-mkrescue -o $@ build/iso

# rebuild if linker.ld changes, but exclude it from the target's prerequisites
build/kernel.bin: OBJ_WITHOUT_LD = $(patsubst %.ld, , $^)
build/kernel.bin: $(OBJ) kernel/linker.ld
	$(CC) $(LDFLAGS) $(OBJ_WITHOUT_LD) $(LDLIBS) -o $@
	grub-file --is-x86-multiboot $@

build/%.c.o: %.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
build/%.S.o: %.S
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

-include $(DEPS)
