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
    server->clients[idx].req = NULL;
    server->clients[idx].username = NULL;
    server->clients[idx].password = NULL;
    server->clients[idx].is_logged = false;
    respond_to(client_sock, "220 Service ready for new user.\r\n");
    new_connection_debug(server->debug, &server->clients[idx]);
}

static void client_request(server_t *serv, int id, int ret, const char *req)
{
    char *cmd = NULL;
    char *data = NULL;

    if (ret == 0)
        return disconnect_client(serv, id);
    parse_cmd(&serv->clients[id].req, req, &cmd, &data);
    if (cmd == NULL && data == NULL)
        return;
    new_request_debug(serv->debug, serv->clients[id].fd, cmd, data);
    if (!strcmp(cmd, "USER"))
        user(data, &serv->clients[id], serv->users, serv->nb_users);
    else if (!strcmp(cmd, "PASS"))
        pass(data, &serv->clients[id], serv->users, serv->nb_users);
    else
        respond_to(serv->clients[id].fd, "500 Unknown command.\r\n");
    free(cmd);
    free(data);
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