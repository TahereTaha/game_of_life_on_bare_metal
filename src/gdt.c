#include "gdt.h"
#include "../include/kernel.h"

struct gdt_entry_t	gdt_entries[3];
struct gdt_ptr_t	gdt_ptr;

void	init_gdt(void)
{
	gdt_ptr.limit = (sizeof(struct gdt_entry_t) * 3) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	set_gdt_gate(0, 0, 0, 0, 0); //	null segment.
	set_gdt_gate(1, 0, 0xffffffff, 0x9a, 0xcf);	//	kernel code.
	set_gdt_gate(2, 0, 0xffffffff, 0x92, 0xcf);	//	kernel data.

	gdt_flush();

	terminal_writestring("seted the gdt.\n");
}

void	set_gdt_gate(	uint32_t num, \
						uint32_t base, \
						uint32_t limit, \
						uint8_t access, \
						uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xffff);
	gdt_entries[num].base_middle = (base >> 16) & 0xff;
	gdt_entries[num].base_high = (base >> 24) & 0xff;

	gdt_entries[num].limit = (limit & 0xffff);
	gdt_entries[num].flags = (limit >> 16) & 0x0f;
	gdt_entries[num].flags |= (gran & 0xf0);
	gdt_entries[num].access = access;

}

