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

void user(const char *req, client_t *client, user_t *users, int nb_users)
{
    if (client->is_logged) {
        write(client->fd, "501 Reauthentication not supported\r\n", 37);
        return;
    }
}