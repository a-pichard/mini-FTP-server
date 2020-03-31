/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

typedef struct {
    char *username;
    char *password;
    char *home;
} user_t;

typedef struct {
    int fd;
    int fd_data;
} client_t;

typedef struct {
    int server_fd;
    int port;
    user_t *users;
    int nb_users;
    client_t *clients;
    int nb_client;
} server_t;

void init_server(server_t *server, int port, const char *);
void destroy_server(server_t *server);
int init_main_server_socket(int port);

#endif /* !SERVER_H_ */