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

void destroy_write_q(write_queue_t *q)
{
    write_queue_t *tmp;

    while (q != NULL) {
        tmp = q->next;
        free(q->msg);
        free(q);
        q = tmp;
    }
}

static void destroy_client(client_t *client)
{
    close(client->fd);
    if (client->username)
        free(client->username);
    if (client->password)
        free(client->password);
    if (client->req)
        free(client->req);
    if (client->home)
        free(client->home);
    if (client->wd)
        free(client->wd);
    if (client->data_fd != -1)
        close(client->data_fd);
    destroy_write_q(client->write_q);
}

static bool empty(server_t *server)
{
    if (server->nb_client == 0) {
        destroy_client(&server->clients[0]);
        new_disconnection_debug(server->debug, server->clients[0].fd);
        free(server->clients);
        server->clients = NULL;
        return (true);
    }
    return (false);
}

void disconnect_client(server_t *server, int id)
{
    int new = 0;
    client_t *clients;

    server->nb_client -= 1;
    if (empty(server))
        return;
    clients = malloc(sizeof(client_t) * (server->nb_client));
    raise_error(clients != NULL, "malloc() ");
    for (int i = 0; i < (server->nb_client + 1); i++) {
        if (i != id) {
            memcpy(&clients[new], &server->clients[i], sizeof(client_t));
            new++;
        } else
            destroy_client(&server->clients[i]);
    }
    new_disconnection_debug(server->debug, server->clients[id].fd);
    free(server->clients);
    server->clients = clients;
}