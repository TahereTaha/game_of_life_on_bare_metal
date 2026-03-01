#include "../include/kernel.h"
#include "gdt.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_buffer = (uint16_t*)VGA_MEMORY;
	terminal_initialize();
	
	//	initialize the gdt to be able to manage interupts.
	init_gdt();

	terminal_writestring("finished initializing the kernel.\n");
	while (1)
	{

	}
}

//
//void kernel_main(void) 
//{
//	/* Initialize terminal interface */
//	terminal_buffer = (uint16_t*)VGA_MEMORY;
//	terminal_initialize();
//	
//	//	initialize the gdt to be able to manage interupts.
//	init_gdt();
//
//	terminal_writestring("Sabias que en portugues perejil se dice salsa?\n");
//	terminal_writestring("Entonces, si un portugues\n");
//	terminal_writestring("pide salsa de perejil\n");
//	terminal_writestring("Que pedira??\n");
//	terminal_writestring("\n");
//	terminal_writestring("\n");
//	setColour(BLUE);
//	terminal_writestring("   _____         _       _____            _____         _       _____         \n");
//	terminal_writestring("  / ____|  /\\   | |     / ____|  /\\      / ____|  /\\   | |     / ____|  /\\    \n");
//	setColour(GREEN);
//	terminal_writestring(" | (___   /  \\  | |    | (___   /  \\    | (___   /  \\  | |    | (___   /  \\   \n");
//	terminal_writestring("  \\___ \\ / /\\ \\ | |     \\___ \\ / /\\ \\    \\___ \\ / /\\ \\ | |     \\___ \\ / /\\ \\  \n");
//	setColour(MAGENTA);
//	terminal_writestring("  ____) / ____ \\| |____ ____) / ____ \\   ____) / ____ \\| |____ ____) / ____ \\ \n");
//	terminal_writestring(" |_____/_/    \\_\\______|_____/_/    \\_\\ |_____/_/    \\_\\______|_____/_/    \\_ \n");
//	terminal_writestring("                                                                              \n");
//}
