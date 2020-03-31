/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** helper
*/

#include <stdio.h>
#include <stdlib.h>

void helper(int exit_status)
{
    puts("USAGE: .myftp port patch");
    puts("\tport is the port number on which the server socket listens");
    puts("\tpath is the path to the home directory for the Anonymous user");
    exit(exit_status);
}