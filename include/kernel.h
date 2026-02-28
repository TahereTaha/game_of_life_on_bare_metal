#ifndef KERNEL_H
# define KERNEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_MEMORY	0xB8000 

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

/* Hardware text mode color constants. */
enum vga_color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

//GENERAL USE FUNCTIONS

void	memcpy_k(void *dest, const void *src, size_t n);
void	memset_k(void *s, int c, size_t n);
size_t	strlen(const char *str);
void	bzero_k(void *s, size_t n);

//TERMINAL/DISPLAY FUNCTIONS

void	terminal_initialize(void);
void	terminal_setcolor(uint8_t color);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	terminal_putchar(char c);
void	terminal_write(const char* data, size_t size);
void	terminal_writestring(const char* data);
void	scroll(void);
int		is_special_character(char c);
void	setColour(enum vga_color c);

#endif
