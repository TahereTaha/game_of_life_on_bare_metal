

ROOT_DIR	=	./

BIN_DIR		=	$(ROOT_DIR)bin/
ISO_DIR		=	$(ROOT_DIR)isodir/
SRC_DIR		=	$(ROOT_DIR)src/
INC_DIR		=	$(ROOT_DIR)inc/

RM		=	rm -rf
AS		=	i686-elf-as
CC		=	i686-elf-gcc

OS_NAME	=	myos

VPATH	= $(ROOT_DIR)
VPATH	+= $(SRC_DIR)

all	: $(OS_NAME)

$(OS_NAME): boot.s kernel.c linker.ld
	mkdir $(BIN_DIR)
	$(AS) boot.s -o $(BIN_DIR)boot.o
	$(CC) -c kernel.c -o $(BIN_DIR)kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T linker.ld -o myos -ffreestanding -O2 -nostdlib $(BIN_DIR)boot.o $(BIN_DIR)kernel.o -lgcc

iso: $(OS_NAME)
	mkdir -p isodir/boot/grub
	cp myos isodir/boot/myos
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

clean:
	$(RM) $(BIN_DIR)
	$(RM) $(ISO_DIR)

fclean:	clean
	$(RM) $(OS_NAME)
	$(RM) $(OS_NAME).iso

re: fclean all

.PHONY:	all iso clean fclean re
