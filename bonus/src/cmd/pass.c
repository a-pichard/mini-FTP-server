/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "cmd.h"
#include "errors.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void pass(char *data, client_t *client, user_t *users, int nusr)
{
    if (client->is_logged) {
        write_q(client, "501 Reauthentication not supported.\r\n", false);
        return;
    }
    if (client->password)
        free(client->password);
    client->password = !!data ? strdup(data) : NULL;
    raise_error(!data || (!!data && !!client->password), "strdup() ");
    if (client->username == NULL)
        write_q(client, "332 Need account for login.\r\n", false);
    else
        auth(client, users, nusr);
}