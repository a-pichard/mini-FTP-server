/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** auth
*/

#include "cmd.h"
#include "errors.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void reset_credentials(client_t *client)
{
    if (client->username != NULL)
        free(client->username);
    client->username = NULL;
    if (client->password != NULL)
        free(client->password);
    client->password = NULL;
}

void check_user(client_t *client, user_t *user)
{
    char *upass = user->password;
    char *cpass = client->password;

    if (!strcmp(upass, "") || !strcmp(upass, cpass)) {
        client->is_logged = true;
        client->home = strdup(user->home);
        raise_error(client->home != NULL, "strdup() ");
        respond_to(client->fd, "230 User logged in, proceed.\r\n");
    } else {
        reset_credentials(client);
        respond_to(client->fd, "530 Login incorrect.\r\n");
    }
}

void auth(client_t *client, user_t *users, int nusr)
{
    for (int i = 0; i < nusr; i++) {
        if (!strcmp(client->username, users[i].username)) {
            check_user(client, &users[i]);
            return;
        }
    }
    reset_credentials(client);
    respond_to(client->fd, "530 Login incorrect.\r\n");
}