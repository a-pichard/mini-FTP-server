/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list_utils
*/

#include "errors.h"
#include <string.h>
#include <stdlib.h>

char *get_cmd_line(const char *dir)
{
    char *cmd;

    cmd = malloc(sizeof(char) * (strlen(dir) + 7));
    raise_error(cmd != NULL, "malloc() ");
    strcpy(cmd, "ls -l ");
    strcat(cmd, dir);
    return (cmd);
}