

ROOT_DIR	=	./

BIN_DIR		=	$(ROOT_DIR)bin/
SRC_DIR		=	$(ROOT_DIR)src/
INC_DIR		=	$(ROOT_DIR)inc/

RM		=	rm -rf
CC		=	

OS_NAME	=	paftah

VPATH	= $(ROOT_DIR)
VPATH	+= $(SRC_DIR)

all	:
	


-include $(DEP)

.PHONY:	all clean fclean re
