/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** control_cmd
*/

#include "cmd.h"
#include "server.h"
#include <string.h>

static cmd_t index_of(const char **narr, cmd_t *funcs, const char *cmd)
{
    int i = 0;

    while (narr[i] != NULL) {
        if (!strcmp(narr[i], cmd))
            return (funcs[i]);
        i++;
    }
    return (NULL);
}

void control_cmds(client_t *client, const char *cmd, const char *data)
{
    cmd_t funcs[] = {};
    cmd_t func = NULL;
    const char *narr[] = {NULL};

    if (!client->is_logged) {
        respond_to(client->fd, "530 Please login with USER and PASS.\r\n");
        return;
    }
    func = index_of(narr, funcs, cmd);
    if (!func)
        respond_to(client->fd, "500 Unknown command.\r\n");
    else
        (func)(client, data);
}