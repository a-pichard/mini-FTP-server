/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "cmd.h"
#include "errors.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void user(char *data, client_t *client, user_t *users, int nusr)
{
    if (client->is_logged) {
        write_q(client, "501 Reauthentication not supported.\r\n", false);
        return;
    } else if (!data || (!!data && !strlen(data))) {
        write_q(client, "530 Permission denied.\r\n", false);
        return;
    }
    if (client->username)
        free(client->username);
    client->username = strdup(data);
    raise_error(client->username != NULL, "strdup() ");
    if (client->password == NULL)
        write_q(client, "331 User name okay, need password.\r\n", false);
    else
        auth(client, users, nusr);
}