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
#include <fcntl.h>
#include <string.h>

static int get_file_fd(client_t *client, const char *data, int flags)
{
    char *path;
    char *real_path;

    if (data == NULL) {
        write_q(client, "550 Missing file path.\r\n", false);
        return (-1);
    }
    if (client->mode == NOMODE || client->data_fd == -1) {
        write_q(client, "425 Use PORT or PASV first.\r\n", false);
        return (-1);
    }
    path = get_path(client->home, client->wd, data);
    real_path = realpath(path, NULL);
    free(path);
    if (!!real_path && real_path == strstr(real_path, client->home))
        return (open_file(client, real_path, flags));
    else {
        free(real_path);
        write_q(client, "550 Could not find file.\r\n", false);
        return (-1);
    }
}

static bool read_n_write(int file_fd, int data_fd)
{
    unsigned char buffer[BUFFER_READ_SIZE] = { 0 };
    int ret_read;
    bool ret_write;

    while ((ret_read = read(file_fd, buffer, BUFFER_READ_SIZE)) > 0) {
        ret_write = write_in_fork(data_fd, buffer, ret_read);
        if (ret_write == false)
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
        if ((fd = accept_connection(client->data_fd)) == -1)
            return (false);
        status = read_n_write(file_fd, fd);
        close(fd);
    }
    return (status);
}

void retr(client_t *client, char *data)
{
    int file_fd = get_file_fd(client, data, O_RDONLY);

    if (file_fd == -1)
        return;
    if (!!(fork())) {
        close(client->data_fd);
        client->data_fd = -1;
        client->mode = NOMODE;
    } else {
        free(data);
        if (send_data(client, file_fd) == false) {
            respond_to(client->fd, "550 Something went wrong.\r\n");
        } else {
            respond_to(client->fd, "226 Closing data connection.\r\n");
        }
        destroy_server();
        close(file_fd);
        exit(0);
    }
}