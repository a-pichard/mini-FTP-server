/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "cmd.h"
#include "errors.h"
#include <unistd.h>
#include <string.h>

void pass(char *data, client_t *client, user_t *users, int nusr)
{
    if (client->is_logged) {
        respond_to(client->fd, "501 Reauthentication not supported.\r\n");
        return;
    }
    client->password = !!data ? strdup(data) : NULL;
    raise_error(!data || (!!data && !!client->password), "strdup() ");
    if (client->username == NULL)
        respond_to(client->fd, "332 Need account for login.\r\n");
    else
        auth(client, users, nusr);
}