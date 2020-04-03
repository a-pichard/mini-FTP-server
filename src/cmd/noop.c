/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "cmd.h"
#include <unistd.h>

void noop(client_t *client, const char *d UNUSED)
{
    respond_to(client->fd, "200 Command okay.\r\n");
}