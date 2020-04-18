/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** type
*/

#include "cmd.h"
#include "string.h"

void type(client_t *client, char *data)
{
    if (!data || strlen(data) != 1) {
        write_q(client, "500 Unrecognised TYPE command.\r\n", false);
        return;
    }
    if (!strcasecmp(data, "i")) {
        write_q(client, "200 Switching to Binary mode.\r\n", false);
    } else if (!strcasecmp(data, "a")) {
        write_q(client, "200 Switching to ASCII mode.\r\n", false);
    } else {
        write_q(client, "500 Unrecognised TYPE command.\r\n", false);
    }
}