/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** get_path
*/

#include "cmd.h"
#include "errors.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *get_path(client_t *client, const char *data)
{
    int len = strlen(client->home) + strlen(client->wd) + strlen(data);
    char *path = malloc(sizeof(char) * (len + 3));

    raise_error(path != NULL, "malloc() ");
    sprintf(path, "%s/%s/%s", client->home, client->wd, data);
    return (path);
}