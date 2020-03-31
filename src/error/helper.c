/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** helper
*/

#include <stdio.h>
#include <stdlib.h>

void helper(const char *prg_name, int exit_status)
{
    dprintf(1, "USAGE: %s port path\n", prg_name);
    dprintf(1, "\tport is the port number on which the server socket listens\n");
    dprintf(1, "\tpath is the path to the home directory for the Anonymous user\n");
    exit(exit_status);
}