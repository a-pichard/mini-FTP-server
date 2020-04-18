/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cdup
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

void cdup(client_t *client, char *data UNUSED)
{
    char *tmp;
    char *parsed;

    tmp = get_path(client->home, client->wd, "..");
    parsed = realpath(tmp, NULL);
    free(tmp);
    if (parsed == NULL)
        return (write_q(client, "550 Failed to change directory.\r\n", false));
    tmp = get_relative_path(client->home, parsed);
    free(parsed);
    free(client->wd);
    if (tmp) {
        client->wd = tmp;
    } else {
        client->wd = strdup("/");
        raise_error(client->wd != NULL, "strdup() ");
    }
    write_q(client, "200 Command okay.\r\n", false);
}