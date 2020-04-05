/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept_connection
*/

#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/select.h>

int accept_connection(int fd)
{
    fd_set rset;
    struct timeval tv;
    int ret;

    tv.tv_sec = 15;
    tv.tv_usec = 0;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    ret = select(fd + 1, NULL, &rset, NULL, &tv);
    if (ret == 0 || !FD_ISSET(fd, &rset))
        return (-1);
    return (accept(fd, NULL, NULL));
}