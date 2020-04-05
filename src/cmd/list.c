/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "cmd.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static char *get_cmd(client_t *client, const char *data)
{
    char *path;
    char *cmd;

    if (client->mode == NOMODE || client->data_fd == -1) {
        write_q(client, "425 Use PORT or PASV first.\r\n", false);
        return (NULL);
    }
    path = get_path(client->home, client->wd, (data == NULL) ? "." : data);
    cmd = malloc(sizeof(char) * (strlen(path) + 7));
    strcpy(cmd, "ls -l ");
    strcat(cmd, path);
    free(path);
    return (cmd);
}

static int get_fd(client_t *client)
{
    struct sockaddr *infos;
    socklen_t len;
    int fd;

    if (client->mode == ACTIVE) {
        infos = (struct sockaddr *)&client->data_info;
        len = sizeof(client->client_info);
        if (connect(client->data_fd, infos, len) == -1) {
            respond_to(client->fd, "500 Connect failed.\r\n");
            return (-1);
        }
        return (client->data_fd);
    } else {
        if ((fd = accept_connection(client->data_fd)) == -1) {
            respond_to(client->fd, "500 Accpect failed.\r\n");
            return (-1);
        }
        return (fd);
    }
}

static bool send_listing(FILE *stream, int fd, transfer_mode_t mode)
{
    int ret_gl;
    char *line = NULL;
    size_t s = 0;
    int skip = true;
    bool ret = true;

    while ((ret_gl = getline(&line, &s, stream)) > 0) {
        if (!skip)
            ret = write_in_fork(fd, line, ret_gl);
        if (ret == false)
            return (false);
        skip = false;
    }
    if (line)
        free(line);
    if (mode == PASSIVE)
        close(fd);
    return (true);
}

static void compute_list(client_t *client, const char *cmd)
{
    FILE *stream;
    int fd = get_fd(client);

    if (fd == -1)
        return;
    stream = popen(cmd, "r");
    if (stream == NULL) {
        respond_to(client->fd, "500 Something went wrong.\r\n");
        return;
    }
    if (send_listing(stream, fd, client->mode)) {
        respond_to(client->fd, "226 Closing data connection.\r\n");
    } else {
        respond_to(client->fd, "500 Something went wrong.\r\n");
    }
    pclose(stream);
}

void list(client_t *client, char *data)
{
    char *cmd = get_cmd(client, data);
    char *ok_msg = "150 File status okay; about to open data connection.\r\n";

    if (cmd == NULL)
        return;
    write_q(client, ok_msg, false);
    if (!!(fork())) {
        free(cmd);
        close(client->data_fd);
        client->data_fd = -1;
        client->mode = NOMODE;
    } else {
        free(data);
        compute_list(client, cmd);
        close(client->data_fd);
        free(cmd);
        destroy_server();
        exit(0);
    }
}