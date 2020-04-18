/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_users
*/

#include "server.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

void init_users(server_t *server, const char *anonymous_home)
{
    user_t *users = malloc(sizeof(user_t));

    raise_error(users != NULL, "malloc() ");
    users[0].username = strdup("Anonymous");
    raise_error(users[0].username != NULL, "strdup() ");
    users[0].password = strdup("");
    raise_error(users[0].password != NULL, "strdup() ");
    users[0].home = realpath(anonymous_home, NULL);
    raise_error(users[0].home != NULL, "realpath() ");
    server->users = users;
    server->nb_users = 1;
}