/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** destroy
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void destroy_users(user_t *users, int nb_users)
{
    if (users == NULL)
        return;
    for (int i = 0; i < nb_users; i++) {
        if (users[i].username != NULL)
            free(users[i].username);
        if (users[i].password != NULL)
            free(users[i].password);
        if (users[i].home != NULL)
            free(users[i].home);
    }
    free(users);
}

static void destroy_clients(client_t *clients, int nb_clients)
{
    if (clients == NULL)
        return;
    for (int i = 0; i < nb_clients; i++) {
        if (clients[i].username != NULL)
            free(clients[i].username);
        if (clients[i].password != NULL)
            free(clients[i].password);
        if (clients[i].req != NULL)
            free(clients[i].req);
        if (clients[i].home != NULL)
            free(clients[i].home);
        if (clients[i].wd != NULL)
            free(clients[i].wd);
        if (clients[i].data_fd != -1)
            close(clients[i].data_fd);
        close(clients[i].fd);
        destroy_write_q(clients[i].write_q);
    }
    free(clients);
}

void destroy_server(void)
{
    server_t *server = server_address(NULL);

    if (server->debug)
        dprintf(1, "\nDestroying the server...\n");
    destroy_users(server->users, server->nb_users);
    destroy_clients(server->clients, server->nb_client);
    close(server->server_fd);
}