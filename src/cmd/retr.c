/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** retr
*/

#include "cmd.h"
#include "errors.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

static int get_file_fd(client_t *client, const char *data)
{
    char *path;
    int fd;
    char *ok_msg = "150 File status okay; about to open data connection.\r\n";

    if (data == NULL) {
        respond_to(client->fd, "500 Missing file path.\r\n");
        return (-1);
    }
    if (client->mode == NOMODE || client->data_fd == -1) {
        respond_to(client->fd, "425 Use PORT or PASV first.\r\n");
        return (-1);
    }
    path = get_path(client, data);
    fd = open(path, O_RDONLY);
    free(path);
    if (fd == -1)
        respond_to(client->fd, "550 Failed to open file.\r\n");
    else
        respond_to(client->fd, ok_msg);
    return (fd);
}

static size_t get_file_size(int fd)
{
    struct stat st;

    fstat(fd, &st);
    return (st.st_size);
}

static void write_to_data_socket(client_t *client, int file_fd, size_t size)
{
    int fd;

    if (client->mode == ACTIVE) {
        connect(client->data_fd, NULL, 0);
        sendfile(client->data_fd, file_fd, NULL, size);
    } else if (client->mode == PASSIVE) {
        fd = accept(client->data_fd, NULL, NULL);
        sendfile(fd, file_fd, NULL, size);
        close(fd);
    }
}

void retr(client_t *client, const char *d)
{
    int file_fd = get_file_fd(client, d);
    int pid;

    if (file_fd == -1)
        return;
    pid = fork();
    raise_error(pid != -1, "fork() ");
    if (!!pid) {
        client->data_fd = -1;
        client->mode = NOMODE;
    } else {
        write_to_data_socket(client, file_fd, get_file_size(file_fd));
        close(file_fd);
        close(client->data_fd);
        respond_to(client->fd, "226 Closing data connection.\r\n");
        exit(0);
    }
}