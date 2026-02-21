org 0x7C00
bits 16

main:
	mov ah, 0x0E
	mov al, 0x41
	mov bh, 0
	mov bl, 0
	int 10h
	hlt

.halt:
	jmp .halt

times 510 - ($-$$) db 0
dw 0x0AA5
