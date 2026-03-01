

ROOT_DIR	=	./

BIN_DIR		=	$(ROOT_DIR)bin/
ISO_DIR		=	$(ROOT_DIR)isodir/
SRC_DIR		=	$(ROOT_DIR)src/
INC_DIR		=	$(ROOT_DIR)inc/

RM			=	rm -rf
AS			=	i686-elf-as
CC			=	i686-elf-gcc
NASM		=	nasm
NASM_FLAGS	=	-felf32 -g

OS_NAME		=	myos

CCFLAGS		:=	-Wall -Wextra -ffreestanding -std=gnu99 -O2

LINK_FILE	=	linker.ld

BOOT_OBJ	=	boot.o			\

OBJ			:=	kernel.o		\
				terminal.o		\
				functions.o		\
				gdt.o			\

OBJ			:=	$(addprefix $(BIN_DIR), $(OBJ))

OBJ_ASM		:=	gdt_flush.o	\

OBJ_ASM		:=	$(addprefix $(BIN_DIR), $(OBJ_ASM))

BOOT_OBJ	:=	$(addprefix $(BIN_DIR), $(BOOT_OBJ))

LINK_FILE	:=	$(addprefix $(SRC_DIR), $(LINK_FILE))

VPATH		= $(ROOT_DIR)
VPATH		+= $(SRC_DIR)

all	: $(BIN_DIR) $(OS_NAME)

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OS_NAME): $(BOOT_OBJ) $(OBJ) $(OBJ_ASM) $(LINK_FILE) Makefile
	$(CC) -T $(LINK_FILE) -o myos $(CCFLAGS) -nostdlib $(BOOT_OBJ) $(OBJ_ASM) $(OBJ) -lgcc

$(BIN_DIR)%.o : %.c	Makefile 
	$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR)%.o : %.s	Makefile 
	$(AS) $< -o $@

$(BIN_DIR)%.o : %.asm	Makefile 
	$(NASM) $(NASM_FLAGS) $< -o $@

iso: $(ISO_DIR) $(OS_NAME)
	cp myos $(ISO_DIR)boot/myos
	cp grub.cfg $(ISO_DIR)boot/grub/grub.cfg
	grub-mkrescue -o myos.iso $(ISO_DIR)

test:
	qemu-system-i386 -kernel myos

$(ISO_DIR):
	mkdir -p $(ISO_DIR)boot/grub

clean:
	$(RM) $(BIN_DIR)
	$(RM) $(ISO_DIR)

fclean:	clean
	$(RM) $(OS_NAME)
	$(RM) $(OS_NAME).iso

re: fclean all

.PHONY:	all iso test clean fclean re
