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
#include <stdlib.h>

void user(const char *data, client_t *client)
{
    if (client->is_logged) {
        write(client->fd, "501 Reauthentication not supported\r\n", 37);
        return;
    }
    client->username = strdup(data);
    write(client->fd, "331 User name okay, need password.\r\n", 37);
}