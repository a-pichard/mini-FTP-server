/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** quit
*/

#include "cmd.h"

void quit(char *d UNUSED, client_t *c, user_t *u UNUSED, int i UNUSED)
{
    write_q(c, "221 Service closing control connection.\r\n", true);
}