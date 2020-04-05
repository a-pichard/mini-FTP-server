/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** quit
*/

#include "cmd.h"

void quit(client_t *client)
{
    write_q(client, "221 Service closing control connection.\r\n", true);
}