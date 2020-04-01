/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** handle_client
*/

#include "server.h"
#include "errors.h"
#include "cmd.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

void accept_new_client_connection(server_t *server)
{
    socklen_t size;
    int client_sock;
    int idx = server->nb_client;
    struct sockaddr *client_info;

    server->clients = realloc(server->clients, sizeof(client_t) * (idx + 1));
    raise_error(server->clients != NULL, "realloc()) ");
    server->nb_client += 1;
    size = sizeof(server->clients[idx].client_info);
    client_info = (struct sockaddr *)(&server->clients[idx].client_info);
    client_sock = accept(server->server_fd, client_info, &size);
    raise_error(client_sock != -1, "accept() ");
    server->clients[idx].fd = client_sock;
    server->clients[idx].is_logged = false;
    server->clients[idx].username = NULL;
    server->clients[idx].passwd = NULL;
    write(client_sock, "220 Service ready for new user.\r\n", 34);
    dprintf(1, "New connection from %s:%u with id: %d\n", inet_ntoa(server->clients[idx].client_info.sin_addr), ntohs(server->clients[idx].client_info.sin_port), server->clients[idx].fd);
}

static void client_request(server_t *serv, int id, int ret, const char *req)
{
    if (ret == 0)
        return disconnect_client(serv, id);
    dprintf(1, "Client with fd %d said: %s", serv->clients[id].fd, req);
    if (!strncmp(req, "USER", 4))
        return user(req, &serv->clients[id], serv->users, serv->nb_users);
}

void handle_client(fd_set *rset, server_t *server)
{
    char buffer[BUFFER_READ_SIZE] = { 0 };
    int ret = 0;

    for (int i = 0; i < server->nb_client; i++) {
        if (FD_ISSET(server->clients[i].fd, rset)) {
            FD_CLR(server->clients[i].fd, rset);
            ret = read(server->clients[i].fd, buffer, BUFFER_READ_SIZE);
            raise_error(ret >= 0, "read() ");
            client_request(server, i, ret, buffer);
            break;
        }
    }
}