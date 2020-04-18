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
		src/cmd/utils/get_path.c	\
		src/cmd/utils/fork.c	\
		src/cmd/utils/open_file.c	\
		src/cmd/utils/list_utils.c	\
		src/cmd/user.c	\
		src/cmd/pass.c	\
		src/cmd/quit.c	\
		src/cmd/pwd.c	\
		src/cmd/noop.c	\
		src/cmd/pasv.c	\
		src/cmd/port.c	\
		src/cmd/retr.c	\
		src/cmd/cwd.c	\
		src/cmd/cdup.c	\
		src/cmd/list.c	\
		src/cmd/stor.c	\
		src/cmd/dele.c	\
		src/cmd/help.c	\
		src/cmd/syst.c	\
		src/cmd/type.c	\
		src/init/init_users.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iincl -Wall -Wextra -g

NAME	=	myftp

TEST_NAME	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) *.gc* tests/client_files/* tests/server_files/*

fclean:	clean
	rm -f $(NAME) $(TEST_NAME)

re:	fclean all

tests_run: clean
	cp tests/transfer_files_test/client* tests/client_files
	cp tests/transfer_files_test/server* tests/server_files
	cp tests/transfer_files_test/to_rm* tests/server_files
	gcc -o $(TEST_NAME) $(SRC) --coverage $(CFLAGS)
	tests/run_tests.sh