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
    unsigned char *path;
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

static bool read_n_write(int file_fd, int data_fd)
{
    char buffer[BUFFER_READ_SIZE] = { 0 };
    int ret_read;
    int ret_write;

    while ((ret_read = read(file_fd, buffer, BUFFER_READ_SIZE)) > 0) {
        ret_write = write(data_fd, buffer, ret_read);
        if (ret_write == -1)
            return (false);
    }
    return (true);
}

static bool send_data(client_t *client, int file_fd)
{
    int fd;
    struct sockaddr *infos;
    socklen_t len;
    bool status = false;

    if (client->mode == ACTIVE) {
        infos = (struct sockaddr *)&client->data_info;
        len = sizeof(client->data_info);
        if (connect(client->data_fd, infos, len) == -1)
            return (false);
        status = read_n_write(file_fd, client->data_fd);
    } else if (client->mode == PASSIVE) {
        if ((fd = accept(client->data_fd, NULL, NULL)) == -1)
            return (false);
        status = read_n_write(file_fd, fd);
        close(fd);
    }
    return (status);
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
        if (send_data(client, file_fd) == false) {
            close(client->data_fd);
            respond_to(client->fd, "500 Something went wrong.\r\n");
        } else {
            close(client->data_fd);
            respond_to(client->fd, "226 Closing data connection.\r\n");
        }
        close(file_fd);
        exit(0);
    }
}