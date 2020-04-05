/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** write_fork
*/

#include <stdlib.h>
#include <stdbool.h>
#include <sys/select.h>
#include <unistd.h>

bool write_in_fork(int fd, void *data, size_t size)
{
    fd_set wset;
    struct timeval tv;
    int ret;

    tv.tv_sec = 15;
    tv.tv_usec = 0;
    FD_ZERO(&wset);
    FD_SET(fd, &wset);
    ret = select(fd + 1, NULL, &wset, NULL, &tv);
    if (ret == 0 || !FD_ISSET(fd, &wset))
        return (false);
    write(fd, data, size);
    return (true);
}