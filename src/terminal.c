#include "../include/kernel.h"

//VGA FUNCTIONS

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

//DISPLAY/TERMINAL FUCNTIONS

static void	line_jump(void)
{
	terminal_column = 0;
	if (++terminal_row == VGA_HEIGHT)
		scroll();
}

void	setColour(enum vga_color c)
{
	if (c < 0 || c > 15)
		return ;
	terminal_color = c;
}

void	scroll(void)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index_dst = y * VGA_WIDTH + x;
			const size_t index_src = (y + 1) * VGA_WIDTH + x;
			memcpy_k((void *) &terminal_buffer[index_dst], (void *) &terminal_buffer[index_src], 1);
		}
	}
	memset_k(&terminal_buffer[(VGA_HEIGHT  - 1) * VGA_WIDTH], 0, VGA_WIDTH);
	terminal_row = VGA_HEIGHT - 1;
}

int	is_special_character(char c)
{
	switch (c)
	{
	case ('\n'):
	{
		line_jump();
		return (1);
	}
	default:
		return (0);
	}
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(LIGHT_GREY, BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (is_special_character(c))
		return ;
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
			//scroll();
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
