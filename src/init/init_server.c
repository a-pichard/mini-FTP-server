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

server_t *server_address(server_t *server)
{
    static server_t *save;

    if (server == NULL)
        return (save);
    save = server;
    return (save);
}

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
    server_address(server);
    server->server_fd = init_main_server_socket(port);
    server->port = port;
    init_users(server, a_home);
    server->clients = NULL;
    server->nb_client = 0;
    server->debug = debug;
}