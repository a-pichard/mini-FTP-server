/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** send
*/

#include "server.h"
#include "errors.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static write_queue_t *get_new_elem(const char *msg, bool disconnection)
{
    write_queue_t *tmp = malloc(sizeof(write_queue_t));

    raise_error(tmp != NULL, "malloc() ");
    tmp->disconnection = disconnection;
    tmp->msg = strdup(msg);
    raise_error(tmp != NULL, "strdup() ");
    tmp->next = NULL;
    return (tmp);
}

void write_q(client_t *client, const char *msg, bool disconnection)
{
    write_queue_t *tmp;

    if (client->write_q == NULL) {
        client->write_q = get_new_elem(msg, disconnection);
    } else {
        tmp = client->write_q;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = get_new_elem(msg, disconnection);
    }
}

void send_message(server_t *server, int id)
{
    client_t *client = &server->clients[id];
    write_queue_t *next;
    bool disconnection = client->write_q->disconnection;

    write(client->fd, client->write_q->msg, strlen(client->write_q->msg));
    next = client->write_q->next;
    free(client->write_q->msg);
    free(client->write_q);
    client->write_q = next;
    if (disconnection)
        disconnect_client(server, id);
}