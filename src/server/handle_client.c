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
    server->clients[idx].username = NULL;
    server->clients[idx].is_logged = false;
    write(client_sock, "220 Service ready for new user.\r\n", 34);
    dprintf(1, "New connection from %s:%u with id: %d\n", inet_ntoa(server->clients[idx].client_info.sin_addr), ntohs(server->clients[idx].client_info.sin_port), server->clients[idx].fd); //debug
}

static void parse_cmd(const char *req, char **cmd, char **data)
{
    int len = strlen(req);
    char *tmp;
    int sep;

    if (!(len >= 2 && req[len - 2] == '\r' && req[len - 1] == '\n'))
        return;
    tmp = strchr(req, ' ');
    if (tmp != NULL) {
        sep = (int)(tmp - req);
        *cmd = strndup(req, sep);
        *data = strndup(&req[sep + 1], strlen(&req[sep + 1]) - 2);
    } else {
        *cmd = strndup(req, strlen(req) - 2);
    }
}

static void client_request(server_t *serv, int id, int ret, const char *req)
{
    char *cmd = NULL;
    char *data = NULL;

    if (ret == 0)
        return disconnect_client(serv, id);
    parse_cmd(req, &cmd, &data);
    if (cmd == NULL && data == NULL)
        return;
    dprintf(1, "Client with fd %d said: \"%s\" --> \"%s\"\n", serv->clients[id].fd, cmd, data ? data : "NULL"); // debug
    if (!strncmp(cmd, "USER", 4))
        user(data, &serv->clients[id]);
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