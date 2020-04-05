/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** parse_cmd
*/

#include "server.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>

static char *check_strdup(const char *s)
{
    char *res = strdup(s);

    raise_error(res != NULL, "strdup() ");
    return (res);
}

static char *my_strcat(const char *s1, const char *s2)
{
    char *res;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i = 0;
    int j = 0;

    res = malloc(sizeof(char) * (len1 + len2 + 1));
    raise_error(res != NULL, "malloc() ");
    for (; i < len1; i++)
        res[i] = s1[i];
    for (; j < len2; j++)
        res[i + j] = s2[j];
    res[i + j] = '\0';
    return (res);
}

static char *get_rqst(char **pbuf, const char *req)
{
    char *tmp;

    if (strstr(req, REQ_END) != NULL) {
        if (*pbuf == NULL) {
            return (check_strdup(req));
        } else {
            tmp = my_strcat(*pbuf, req);
            free(*pbuf);
            *pbuf = NULL;
            return (tmp);
        }
    } else {
        if (*pbuf == NULL) {
            *pbuf = check_strdup(req);
        } else {
            tmp = my_strcat(*pbuf, req);
            free(*pbuf);
            *pbuf = tmp;
        }
        return (NULL);
    }
}

static void final_checks(char *rqst, char **cmd, char **data)
{
    if (!(*cmd))
        return;
    if (!strlen(*cmd) && !(*data)) {
        free(*cmd);
        *cmd = NULL;
    }
    free(rqst);
}

void parse_cmd(char **pbuf, const char *req, char **cmd, char **data)
{
    char *tmp;
    char *tmp_end;
    int sep;
    int size;
    char *rqst = get_rqst(pbuf, req);

    if (!rqst)
        return;
    tmp_end = strstr(rqst, REQ_END);
    size = tmp_end - rqst;
    tmp = strchr(rqst, ' ');
    if (tmp != NULL) {
        sep = (int)(tmp - rqst);
        *cmd = strndup(rqst, sep);
        *data = strndup(&rqst[sep + 1], size - sep - 1);
    } else {
        *cmd = strndup(rqst, size);
    }
    final_checks(rqst, cmd, data);
}