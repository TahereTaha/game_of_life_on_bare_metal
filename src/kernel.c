#include "../include/kernel.h"

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
	terminal_writestring("salsa\nsalsa");
}
