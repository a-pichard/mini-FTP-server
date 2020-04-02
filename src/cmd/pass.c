/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "cmd.h"
#include <unistd.h>
#include <string.h>

void pass(const char *data, client_t *client, user_t *users, int nusr)
{
    if (client->is_logged) {
        write(client->fd, "501 Reauthentication not supported.\r\n", 37);
        return;
    }
    client->password = !data ? strdup(data) : NULL;
    if (client->username == NULL)
        write(client->fd, "332 Need account for login.\r\n", 30);
    else
        auth(client, users, nusr);
}