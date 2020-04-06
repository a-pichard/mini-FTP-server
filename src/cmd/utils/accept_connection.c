/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept_connection
*/

#include "cmd.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/select.h>

int accept_connection(int fd)
{
    fd_set rset;
    struct timeval tv;
    int ret;

    tv.tv_sec = TIMEOUT_IN_SEC;
    tv.tv_usec = 0;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    ret = select(fd + 1, &rset, NULL, NULL, &tv);
    if (ret == 0 || !FD_ISSET(fd, &rset))
        return (-1);
    return (accept(fd, NULL, NULL));
}