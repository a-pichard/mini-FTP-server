/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** debug
*/

#include "server.h"
#include <stdio.h>

void new_connection_debug(bool debug, client_t *client)
{
    char *ip;
    unsigned int port;
    int id;

    if (debug) {
        ip = inet_ntoa(client->client_info.sin_addr);
        port = ntohs(client->client_info.sin_port);
        id = client->fd;
        dprintf(1, "New connection from %s:%u with id: %d\n", ip, port, id);
    }
}

void new_request_debug(bool debug, int fd, const char *cmd, const char *data)
{
    char *patern;

    if (debug) {
        patern = "Client with fd %d said: \"%s\" --> \"%s\"\n";
        dprintf(1, patern, fd, cmd, data ? data : "NULL");
    }
}

void new_disconnection_debug(bool debug, int fd)
{
    if (debug)
        dprintf(1, "User with fd %d disconnected\n", fd);
}