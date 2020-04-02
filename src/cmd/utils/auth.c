/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** auth
*/

#include "cmd.h"
#include <string.h>
#include <unistd.h>

void check_user(client_t *client, user_t *user)
{
    char *user_pass = user->password;
    char *client_pass = client->password;

    if (!strcmp(user_pass, "") || !strcmp(user_pass, client_pass)) {
        client->is_logged = true;
        write(client->fd, "230 User logged in, proceed.\r\n", 31);
    } else {
        write(client->fd, "530 Login incorrect.\r\n", 23);
    }
}

void auth(client_t *client, user_t *users, int nusr)
{
    for (int i = 0; i < nusr; i++) {
        if (!strcmp(client->username, users[i].username)) {
            check_user(client, &users[i]);
            break;
        }
    }
}