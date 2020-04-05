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

    if (!data || !strcmp(data, ""))
        return (write_q(client, "550 Failed to change directory.\r\n", false));
    tmp = get_path(client->home, client->wd, data);
    parsed = realpath(tmp, NULL);
    free(tmp);
    if (parsed == NULL)
        return (write_q(client, "550 Failed to change directory.\r\n", false));
    tmp = get_relative_path(client->home, parsed);
    free(parsed);
    if (tmp) {
        free(client->wd);
        client->wd = tmp;
    }
    write_q(client, "250 Requested file action okay, completed.\r\n", false);
}