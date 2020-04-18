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

static char *super_strcat(const char *s1, const char *s2, const char *s3)
{
    int len = strlen(s1) + strlen(s2) + 3 + ((s3 == NULL) ? 0 : strlen(s3));
    char *res = malloc(sizeof(char) * (len + 1));
    int i = 0;
    int j = 0;
    int k = 0;

    raise_error(res != NULL, "malloc() ");
    for (; s1[i] != '\0'; i++)
        res[i] = s1[i];
    res[i++] = '/';
    for (; s2[j] != '\0'; j++)
        res[i + j] = s2[j];
    res[i++ + j] = ((s3 == NULL) ? '\0' : '/');
    if (s3 != NULL) {
        for (; s3[k] != '\0'; k++)
            res[i + j + k] = s3[k];
    }
    res[i + j + k] = '\0';
    return (res);
}

char *get_path(const char *h, const char *wd, const char *data)
{
    if (data[0] == '/')
        return (super_strcat(h, data, NULL));
    else
        return (super_strcat(h, wd, data));
}

char *get_relative_path(const char *h, const char *parsed)
{
    char *path;

    if (parsed == strstr(parsed, h)) {
        if (!strcmp(parsed, h))
            path = strdup("/");
        else
            path = strdup(&parsed[strlen(h)]);
    } else {
        path = strdup("/");
    }
    raise_error(path != NULL, "strdup() ");
    return (path);
}