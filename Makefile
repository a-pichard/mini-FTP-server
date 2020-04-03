##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/debug.c	\
		src/error/helper.c	\
		src/error/input_error_handling.c	\
		src/error/raise_error.c	\
		src/init/init_server.c	\
		src/init/init_socket.c	\
		src/init/destroy.c	\
		src/server/server.c	\
		src/server/parse_cmd.c	\
		src/server/handle_client.c	\
		src/server/disconnect_client.c	\
		src/server/control_cmd.c	\
		src/server/send.c	\
		src/cmd/utils/auth.c	\
		src/cmd/user.c	\
		src/cmd/pass.c	\
		src/cmd/quit.c	\
		src/cmd/pwd.c	\
		src/cmd/noop.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iincl -Wall -Wextra -g

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) -g

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all