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

static log_f_t index_of(const char **narr, log_f_t *funcs, char *cmd)
{
    int i = 0;

    while (narr[i] != NULL) {
        if (!strcasecmp(narr[i], cmd)) {
            free(cmd);
            return (funcs[i]);
        }
        i++;
    }
    return (NULL);
}

static void client_request(server_t *serv, int id, int ret, const char *req)
{
    char *cmd = NULL;
    char *data = NULL;
    log_f_t funcs[] = {&user, &pass, &quit, &help};
    log_f_t func = NULL;
    const char *log_n[] = {"USER", "PASS", "QUIT", "HELP", NULL};

    if (ret == 0)
        return disconnect_client(serv, id);
    parse_cmd(&serv->clients[id].req, req, &cmd, &data);
    if (cmd == NULL && data == NULL)
        return;
    new_request_debug(serv->debug, serv->clients[id].fd, cmd, data);
    if ((func = index_of(log_n, funcs, cmd)) != NULL)
        (func)(data, &serv->clients[id], serv->users, serv->nb_users);
    else
        control_cmds(&serv->clients[id], cmd, data);
    if (data != NULL)
        free(data);
}

void handle_client(server_t *server, int id)
{
    char buffer[BUFFER_READ_SIZE] = { 0 };
    int ret = 0;

    ret = read(server->clients[id].fd, buffer, BUFFER_READ_SIZE);
    raise_error(ret >= 0, "read() ");
    client_request(server, id, ret, buffer);
}