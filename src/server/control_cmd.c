/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** control_cmd
*/

#include "cmd.h"
#include "server.h"

void control_cmds(client_t *client, const char *cmd, const char *data)
{
    cmd;
    data;
    respond_to(client->fd, "500 Unknown command.\r\n");
}