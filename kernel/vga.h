#ifndef VGA_H_INCLUDED
#define VGA_H_INCLUDED

#include <stdint.h>

extern const int VGA_WIDTH, VGA_HEIGHT;
extern const uint8_t VGA_ATTRIBUTES;
extern volatile uint16_t *const vga_buffer;

uint16_t vga_character(char, uint8_t);

#endif // ifndef VGA_H_INCLUDED
