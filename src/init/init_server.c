/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_server
*/

#include "server.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void init_users(server_t *server, const char *anonymous_home)
{
    user_t *users = malloc(sizeof(user_t));

    raise_error(users != NULL, "malloc() ");
    users[0].username = strdup("Anonymous");
    users[0].password = strdup("");
    users[0].home = strdup(anonymous_home);
    server->users = users;
    server->nb_users = 1;
}

void init_server(server_t *server, int port, const char *a_home, bool debug)
{
    server->server_fd = init_main_server_socket(port);
    server->port = port;
    init_users(server, a_home);
    server->clients = NULL;
    server->nb_client = 0;
    server->debug = debug;
}

void destroy_server(server_t *server)
{
    for (int i = 0; i < server->nb_users; i++) {
        free(server->users[i].username);
        free(server->users[i].password);
        free(server->users[i].home);
    }
    if (server->users != NULL)
        free(server->users);
    if (server->clients != NULL)
        free(server->clients);
    close(server->server_fd);
}