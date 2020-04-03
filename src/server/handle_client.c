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

static log_f_t index_of(const char **narr, log_f_t *funcs, const char *cmd)
{
    int i = 0;

    while (narr[i] != NULL) {
        if (!strcmp(narr[i], cmd))
            return (funcs[i]);
        i++;
    }
    return (NULL);
}

static void client_request(server_t *serv, int id, int ret, const char *req)
{
    char *cmd = NULL;
    char *data = NULL;
    log_f_t funcs[] = {&user, &pass};
    log_f_t func = NULL;
    const char *log_n[] = {"USER", "PASS", NULL};

    if (ret == 0)
        return disconnect_client(serv, id);
    parse_cmd(&serv->clients[id].req, req, &cmd, &data);
    if (cmd == NULL && data == NULL)
        return;
    new_request_debug(serv->debug, serv->clients[id].fd, cmd, data);
    if ((func = index_of(log_n, funcs, cmd)) != NULL)
        (func)(data, &serv->clients[id], serv->users, serv->nb_users);
    else if (!strcmp(cmd, "QUIT"))
        quit(serv, id);
    else
        control_cmds(&serv->clients[id], cmd, data);
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