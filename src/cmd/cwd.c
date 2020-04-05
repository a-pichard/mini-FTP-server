/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void cwd(client_t *client, char *data)
{
    char *tmp;
    char *parsed;
    char *ok_msg = "250 Requested file action okay, completed.\r\n";

    if (!data || !strcmp(data, ""))
        return (respond_to(client->fd, "550 Failed to change directory.\r\n"));
    tmp = get_path(client->home, client->wd, data);
    parsed = realpath(tmp, NULL);
    free(tmp);
    if (parsed == NULL)
        return (respond_to(client->fd, "550 Failed to change directory.\r\n"));
    tmp = get_relative_path(client->home, parsed);
    free(parsed);
    if (tmp) {
        free(client->wd);
        client->wd = tmp;
        respond_to(client->fd, ok_msg);
    } else
        respond_to(client->fd, "530 Permission denied.\r\n");
}