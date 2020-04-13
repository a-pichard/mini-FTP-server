/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** syst
*/

#include "cmd.h"

void syst(client_t *client, char *data UNUSED)
{
    write_q(client, "215 UNIX Type: L8\r\n", false);
}