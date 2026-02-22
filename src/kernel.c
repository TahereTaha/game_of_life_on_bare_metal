#include "../include/kernel.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void kernel_main(void) 
{
	terminal_buffer = (uint16_t*)VGA_MEMORY;
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_writestring("salsa\nsalsa");
}
