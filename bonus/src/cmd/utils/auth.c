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
        write_q(client, "230 User logged in, proceed.\r\n", false);
    } else {
        reset_credentials(client);
        write_q(client, "530 Login incorrect.\r\n", false);
    }
}

void auth(client_t *client, user_t *users, int nusr)
{
    for (int i = 0; i < nusr; i++) {
        if (!strcasecmp(client->username, users[i].username)) {
            check_user(client, &users[i]);
            return;
        }
    }
    reset_credentials(client);
    write_q(client, "530 Login incorrect.\r\n", false);
}