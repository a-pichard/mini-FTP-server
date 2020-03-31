##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/error/helper.c	\
		src/error/input_error_handling.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iincl

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all