/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "cmd.h"
#include <unistd.h>

void noop(client_t *client, char *data UNUSED)
{
    write_q(client, "200 Command okay.\r\n", false);
}