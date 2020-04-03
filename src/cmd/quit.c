/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** quit
*/

#include "server.h"

void quit(server_t *server, int id)
{
    char disconnection_msg[] = "221 Service closing control connection.\r\n";
    respond_to(server->clients[id].fd, disconnection_msg);
    disconnect_client(server, id);
}