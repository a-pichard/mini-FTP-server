/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "cmd.h"
#include "errors.h"
#include <unistd.h>
#include <string.h>

void user(const char *data, client_t *client, user_t *users, int nusr)
{
    if (client->is_logged) {
        write(client->fd, "501 Reauthentication not supported.\r\n", 37);
        return;
    } else if (!data || (!!data && !strlen(data))) {
        write(client->fd, "530 Permission denied.\r\n", 25);
        return;
    }
    client->username = strdup(data);
    if (client->password == NULL)
        write(client->fd, "331 User name okay, need password.\r\n", 37);
    else
        auth(client, users, nusr);
}