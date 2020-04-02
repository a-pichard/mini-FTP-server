/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#define MAX_CLIENTS_QUEUE 5
#define BUFFER_READ_SIZE 4096
#define REQ_END "\r\n"

#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/select.h>

typedef struct {
    char *username;
    char *password;
    char *home;
} user_t;

typedef struct {
    int fd;
    struct sockaddr_in client_info;
    char *req;
    char *username;
    char *password;
    bool is_logged;
} client_t;

typedef struct {
    int server_fd;
    int port;
    user_t *users;
    int nb_users;
    client_t *clients;
    int nb_client;
    bool debug;
} server_t;

// Init
void init_server(server_t *, int, const char *, bool);
server_t *server_address(server_t *server);
void destroy_server(void);
int init_main_server_socket(int);

// Server
void handle_client(fd_set *, server_t *);
void disconnect_client(server_t *, int);
void respond_to(int fd, const char *msg);
void parse_cmd(char **, const char *, char **, char **);
void control_cmds(client_t *, const char *, const char *);

//main function
void run_server(server_t *);

//debug
void new_connection_debug(bool, client_t *);
void new_request_debug(bool, int, const char *, const char *);
void new_disconnection_debug(bool, int);

#endif /* !SERVER_H_ */