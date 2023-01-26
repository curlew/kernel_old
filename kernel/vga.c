#include "vga.h"

const int VGA_WIDTH = 80, VGA_HEIGHT = 25;

// white text (15) on cyan background (3)
const uint8_t VGA_ATTRIBUTES = (3 << 4) | 15;

// VGA video memory, color text mode segment (32 KB).
// each screen character is represented by two bytes (uint16_t).
// the low-order byte is the character, the high-order byte is the attributes.
// see vga_character function.
volatile uint16_t *const vga_buffer = (uint16_t *)0xB8000;

uint16_t vga_character(char c, uint8_t attrib) {
    // low-order byte is character, high-order byte is attributes
    return (attrib << 8) | c;
}
