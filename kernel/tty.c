#include "tty.h"

#include "vga.h"

static int cursor_x = 0, cursor_y = 0;

void clear(void) {
    cursor_x = cursor_y = 0;

    for (int index = 0; index < VGA_WIDTH * VGA_HEIGHT; ++index) {
        *(vga_buffer + index) = vga_character(0, VGA_ATTRIBUTES);
    }
}

void putchar(char c) {
    if (c == '\n') {
        goto new_line;
    }

    // VGA buffer is left-to-right then top-to-bottom
    const int index = cursor_x + cursor_y * VGA_WIDTH;
    *(vga_buffer + index) = vga_character(c, VGA_ATTRIBUTES);

    if (++cursor_x == VGA_WIDTH) {
new_line:
        cursor_x = 0;
        if (++cursor_y == VGA_HEIGHT) {
            // TODO: scrolling
            cursor_y = 0;
        }
    }
}

void puts(const char *s) {
    while (*s) {
        putchar(*s++);
    }
    putchar('\n');
}
