/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** stor
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int get_file_fd(client_t *client, const char *data)
{
    char *path;
    int fd;
    char okmsg[] = "150 Opening BINARY mode data connection.\r\n";

    if (data == NULL) {
        write_q(client, "550 Missing file path.\r\n", false);
        return (-1);
    }
    if (client->mode == NOMODE || client->data_fd == -1) {
        write_q(client, "425 Use PORT or PASV first.\r\n", false);
        return (-1);
    }
    path = get_path(client->home, client->wd, data);
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(path);
    if (fd == -1)
        write_q(client, "550 Failed to create file.\r\n", false);
    else
        write_q(client, okmsg, false);
    return (fd);
}

static bool read_n_write(int file_fd, int data_fd)
{
    unsigned char buffer[BUFFER_READ_SIZE] = { 0 };
    int ret_read = 0;

    while ((ret_read = read_in_fork(data_fd, buffer, BUFFER_READ_SIZE)) > 0) {
        write(file_fd, buffer, ret_read);
    }
    if (ret_read == -1)
            return (false);
    return (true);
}

static bool receive_data(client_t *client, int file_fd)
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

void stor(client_t *client, char *data)
{
    int file_fd = get_file_fd(client, data);

    if (file_fd == -1)
        return;
    if (!!(fork())) {
        close(client->data_fd);
        client->data_fd = -1;
        client->mode = NOMODE;
    } else {
        free(data);
        if (receive_data(client, file_fd) == false) {
            respond_to(client->fd, "550 Something went wrong.\r\n");
        } else {
            respond_to(client->fd, "226 Closing data connection.\r\n");
        }
        destroy_server();
        close(file_fd);
        exit(0);
    }
}