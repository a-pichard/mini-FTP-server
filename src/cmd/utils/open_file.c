/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** directory
*/

#include "cmd.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

bool is_regular_file(const char *path)
{
    struct stat st;
    int ret = stat(path, &st);

    if (ret == -1)
        return (false);
    return (S_ISREG(st.st_mode));
}

int open_file(client_t *c, char *path)
{
    int fd;
    char okmsg[] = "150 File status okay; about to open data connection.\r\n";

    if (!is_regular_file(path)) {
        write_q(c, "550 Is a directory.\r\n", false);
        free(path);
        return (-1);
    }
    fd = open(path, O_RDONLY);
    free(path);
    write_q(c, ((fd == -1) ? "550 Failed to open file.\r\n" : okmsg), false);
    return (fd);
}