/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** write_fork
*/

#include "cmd.h"
#include <stdlib.h>
#include <stdbool.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

bool write_in_fork(int fd, void *data, size_t size)
{
    fd_set wset;
    struct timeval tv;
    int ret;

    tv.tv_sec = TIMEOUT_IN_SEC;
    tv.tv_usec = 0;
    FD_ZERO(&wset);
    FD_SET(fd, &wset);
    ret = select(fd + 1, NULL, &wset, NULL, &tv);
    if (ret == 0 || !FD_ISSET(fd, &wset))
        return (false);
    write(fd, data, size);
    return (true);
}

int read_in_fork(int fd, void *data, size_t size)
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
    return (read(fd, data, size));
}

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

void respond_to(int fd, const char *msg)
{
    fd_set wset;
    struct timeval tv;
    int ret;

    tv.tv_sec = TIMEOUT_IN_SEC;
    tv.tv_usec = 0;
    FD_ZERO(&wset);
    FD_SET(fd, &wset);
    ret = select(fd + 1, NULL, &wset, NULL, &tv);
    if (ret == 0 || !FD_ISSET(fd, &wset))
        exit(1);
    write(fd, msg, strlen(msg));
}