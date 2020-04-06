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

int open_file(client_t *c, char *path)
{
    struct stat st;
    int ret = stat(path, &st);
    char okmsg[] = "150 File status okay; about to open data connection.\r\n";

    if (ret == -1 || !S_ISREG(st.st_mode)) {
        write_q(c, "550 Is a directory.\r\n", false);
        free(path);
        return (-1);
    }
    ret = open(path, O_RDONLY);
    free(path);
    write_q(c, ((ret == -1) ? "550 Failed to open file.\r\n" : okmsg), false);
    return (ret);
}