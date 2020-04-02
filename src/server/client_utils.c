/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_utils
*/

#include "errors.h"
#include "server.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void disconnect_client(server_t *server, int id)
{
    int old_idx = 0;
    int new_idx = 0;
    client_t *clients = malloc(sizeof(client_t) * (server->nb_client - 1));

    raise_error(clients != NULL, "malloc() ");
    close(server->clients[id].fd);
    while (old_idx < server->nb_client) {
        if (old_idx != id) {
            memcpy(&clients[new_idx], &server->clients[old_idx], sizeof(client_t));
            new_idx++;
        }
        old_idx++;
    }
    server->nb_client -= 1;
    new_disconnection_debug(server->debug, server->clients[id].fd);
    free(server->clients);
    server->clients = clients;
}