##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/error/helper.c	\
		src/error/input_error_handling.c	\
		src/error/raise_error.c	\
		src/init/init_server.c	\
		src/init/init_socket.c	\
		src/server/server.c	\
		src/server/handle_client.c	\
		src/server/client_utils.c	\
		src/cmd/user.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iincl -Wall -Wextra

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all