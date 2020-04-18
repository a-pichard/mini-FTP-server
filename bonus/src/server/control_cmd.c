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
        if (!strcasecmp(narr[i], cmd)) {
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
    cmd_t funcs[] = F_FUNC;
    cmd_t func = NULL;
    const char *narr[] = F_NAME;

    if (!client->is_logged) {
        write_q(client, "530 Please login with USER and PASS.\r\n", false);
        free(cmd);
        return;
    }
    func = index_of(narr, funcs, cmd);
    if (!func) {
        write_q(client, "500 Unknown command.\r\n", false);
    } else
        (func)(client, data);
}