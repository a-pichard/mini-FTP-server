/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static char *get_path_cwd(client_t *client, const char *data)
{
    char *tmp;
    char *parsed;
    struct stat st;

    tmp = get_path(client->home, client->wd, data);
    parsed = realpath(tmp, NULL);
    free(tmp);
    if (parsed == NULL || stat(parsed, &st) != 0 || !S_ISDIR(st.st_mode)) {
        if (parsed != NULL)
            free(parsed);
        return (NULL);
    }
    tmp = get_relative_path(client->home, parsed);
    free(parsed);
    return (tmp);
}

void cwd(client_t *client, char *data)
{
    char *path;
    char okmsg[] = "250 Requested file action okay, completed.\r\n";

    if (!data || !strcmp(data, ""))
        return (write_q(client, "550 Failed to change directory.\r\n", false));
    path = get_path_cwd(client, data);
    if (path) {
        free(client->wd);
        client->wd = path;
        write_q(client, okmsg, false);
    } else
        write_q(client, "550 Failed to change directory.\r\n", false);
}