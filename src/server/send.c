/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** send
*/

#include <string.h>
#include <unistd.h>

void respond_to(int fd, const char *msg)
{
    write(fd, msg, strlen(msg));
}