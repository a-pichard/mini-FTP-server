/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static bool check_path_dele(client_t *c, char *parsed)
{
    struct stat st;

    if (parsed == NULL) {
        write_q(c, "550 Unable to delete file.\r\n", false);
        return (false);
    } else if (stat(parsed, &st) != 0) {
        free(parsed);
        write_q(c, "550 Unable to delete file.\r\n", false);
        return (false);
    }
    if (S_ISDIR(st.st_mode)) {
        free(parsed);
        write_q(c, "550 Is a Directory.\r\n", false);
        return (false);
    } else if (strstr(parsed, c->home) != parsed) {
        free(parsed);
        write_q(c, "550 Unable to delete file.\r\n", false);
        return (false);
    }
    return (true);
}

void dele(client_t *c, char *data)
{
    char *tmp;
    char *parsed;
    int ret;

    if (!data || !strlen(data))
        return write_q(c, "501 Invalid number of parameters.\r\n", false);
    tmp = get_path(c->home, c->wd, data);
    parsed = realpath(tmp, NULL);
    free(tmp);
    if (!check_path_dele(c, parsed))
        return;
    ret = remove(parsed);
    free(parsed);
    if (ret == 0)
        write_q(c, "250 Requested file action okay, completed.\r\n", false);
    else
        write_q(c, "550 Unable to delete file\r\n", false);
}