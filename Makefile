

ROOT_DIR	=	./

BIN_DIR		=	$(ROOT_DIR)bin/
ISO_DIR		=	$(ROOT_DIR)isodir/
SRC_DIR		=	$(ROOT_DIR)src/
INC_DIR		=	$(ROOT_DIR)inc/

RM			=	rm -rf
AS			=	i686-elf-as
CC			=	i686-elf-gcc

OS_NAME		=	myos

CCFLAGS		:=	-Wall -Wextra -ffreestanding -std=gnu99 -O2

LINK_FILE	=	linker.ld

BOOT_OBJ	=	boot.o			\

OBJ			:=	kernel.o		\

OBJ			:=	$(addprefix $(BIN_DIR), $(OBJ))

BOOT_OBJ	:=	$(addprefix $(BIN_DIR), $(BOOT_OBJ))

LINK_FILE	:=	$(addprefix $(SRC_DIR), $(LINK_FILE))

VPATH		= $(ROOT_DIR)
VPATH		+= $(SRC_DIR)

all	: $(BIN_DIR) $(OS_NAME)

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OS_NAME): $(BOOT_OBJ) $(OBJ) $(LINK_FILE) Makefile
	$(CC) -T $(LINK_FILE) -o myos $(CCFLAGS) -nostdlib $(BOOT_OBJ) $(OBJ) -lgcc

$(BIN_DIR)%.o : %.c	Makefile 
	$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR)%.o : %.s	Makefile 
	$(AS) $< -o $@

iso: $(ISO_DIR) $(OS_NAME)
	cp myos $(ISO_DIR)boot/myos
	cp grub.cfg $(ISO_DIR)boot/grub/grub.cfg
	grub-mkrescue -o myos.iso $(ISO_DIR)

$(ISO_DIR):
	mkdir -p $(ISO_DIR)boot/grub

clean:
	$(RM) $(BIN_DIR)
	$(RM) $(ISO_DIR)

fclean:	clean
	$(RM) $(OS_NAME)
	$(RM) $(OS_NAME).iso

re: fclean all

.PHONY:	all iso clean fclean re
