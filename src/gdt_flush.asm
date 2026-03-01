global gdt_flush

gdt_flush:
	extern gdt_ptr ; gdt.c

	lgdt [gdt_ptr]
	mov ax, 0x10 ; https://stackoverflow.com/questions/23978486/far-jump-in-gdt-in-bootloader
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x8:.flush
.flush:
	ret
