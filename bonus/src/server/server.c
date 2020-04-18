/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#include "server.h"
#include "errors.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void init_new_client(client_t *client, int client_sock)
{
    client->fd = client_sock;
    client->data_fd = -1;
    client->req = NULL;
    client->username = NULL;
    client->password = NULL;
    client->is_logged = false;
    client->home = NULL;
    client->wd = strdup("/");
    raise_error(client->wd != NULL, "strdup() ");
    client->mode = NOMODE;
    client->write_q = NULL;
}

static void accept_new_client_connection(server_t *server)
{
    socklen_t size;
    int client_sock;
    int idx = server->nb_client;
    struct sockaddr *client_info;
    char *ok_msg = "220 Service ready for new user.\r\n";

    server->clients = realloc(server->clients, sizeof(client_t) * (idx + 1));
    raise_error(server->clients != NULL, "realloc()) ");
    server->nb_client += 1;
    size = sizeof(server->clients[idx].client_info);
    client_info = (struct sockaddr *)(&server->clients[idx].client_info);
    client_sock = accept(server->server_fd, client_info, &size);
    raise_error(client_sock != -1, "accept() ");
    init_new_client(&server->clients[idx], client_sock);
    write_q(&server->clients[idx], ok_msg, false);
    new_connection_debug(server->debug, &server->clients[idx]);
}

static int reset_selected_fd(server_t *server, fd_set *rset, fd_set *wset)
{
    int max_fd = server->server_fd;

    FD_ZERO(wset);
    FD_ZERO(rset);
    FD_SET(server->server_fd, rset);
    for (int i = 0; i < server->nb_client; i++) {
        FD_SET(server->clients[i].fd, rset);
        if (server->clients[i].write_q != NULL)
            FD_SET(server->clients[i].fd, wset);
        if (server->clients[i].fd > max_fd)
            max_fd = server->clients[i].fd;
    }
    return (max_fd + 1);
}

static void parse_io(server_t *server, fd_set *rset, fd_set *wset)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (FD_ISSET(server->clients[i].fd, rset))
            handle_client(server, i);
    }
    for (int i = 0; i < server->nb_client; i++) {
        if (FD_ISSET(server->clients[i].fd, wset))
            send_message(server, i);
    }
}

void run_server(server_t *server)
{
    int max_fd;
    int nb_fd_ready;
    fd_set rset;
    fd_set wset;

    while (1) {
        max_fd = reset_selected_fd(server, &rset, &wset);
        nb_fd_ready = select(max_fd, &rset, &wset, NULL, NULL);
        raise_error(nb_fd_ready != -1, "select() ");
        if (FD_ISSET(server->server_fd, &rset)) {
            accept_new_client_connection(server);
            FD_CLR(server->server_fd, &rset);
            nb_fd_ready--;
        }
        parse_io(server, &rset, &wset);
    }
}