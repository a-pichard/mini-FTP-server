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

void dele(client_t *c, char *data)
{
    char *path;
    int ret;

    if (!data || !strlen(data)) {
        write_q(c, "501 Invalid number of parameters.\r\n", false);
        return;
    }
    path = get_path(c->home, c->wd, data);
    if (!is_regular_file(path)) {
        free(path);
        write_q(c, "550 Is a directory.\r\n", false);
        return;
    }
    ret = remove(path);
    free(path);
    if (ret == 0)
        write_q(c, "250 Requested file action okay, completed.\r\n", false);
    else
        write_q(c, "550 Unable to delete file", false);
}