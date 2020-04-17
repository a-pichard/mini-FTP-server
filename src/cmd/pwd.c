/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

void pwd(client_t *client, char *data UNUSED)
{
    char *res = calloc(strlen(client->wd) + 18, sizeof(char));

    raise_error(res != NULL, "calloc() ");
    strcat(res, "257 \"");
    strcat(res, client->wd);
    strcat(res, "\" created.\r\n");
    write_q(client, res, false);
    free(res);
}