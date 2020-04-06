/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "cmd.h"

void help(char *d UNUSED, client_t *c UNUSED, user_t *u UNUSED, int i UNUSED)
{
    write_q(c, "214 You should call 911\r\n", false);
}