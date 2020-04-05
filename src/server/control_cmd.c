/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** control_cmd
*/

#include "cmd.h"
#include "server.h"
#include <string.h>
#include <stdlib.h>

static cmd_t index_of(const char **narr, cmd_t *funcs, char *cmd)
{
    int i = 0;
    cmd_t command = NULL;

    while (narr[i] != NULL) {
        if (!strcmp(narr[i], cmd)) {
            command = funcs[i];
            break;
        }
        i++;
    }
    free(cmd);
    return (command);
}

void control_cmds(client_t *client, char *cmd, char *data)
{
    cmd_t funcs[] = {&pwd, &noop, &pasv, &port, &retr, &cwd, &cdup, &list};
    cmd_t func = NULL;
    const char *narr[] = {"PWD", "NOOP", "PASV", "PORT", "RETR", "CWD", "CDUP", "LIST", NULL};

    if (!client->is_logged) {
        respond_to(client->fd, "530 Please login with USER and PASS.\r\n");
        free(cmd);
        return;
    }
    func = index_of(narr, funcs, cmd);
    if (!func) {
        respond_to(client->fd, "500 Unknown command.\r\n");
    } else
        (func)(client, data);
}