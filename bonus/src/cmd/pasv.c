/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pasv
*/

#include "cmd.h"
#include "errors.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

static void init_socket(client_t *client, struct sockaddr_in *sin)
{
    int ret;
    socklen_t size;

    if (client->data_fd != -1)
        close(client->data_fd);
    client->data_fd = socket(AF_INET, SOCK_STREAM, 0);
    raise_error(client->data_fd != -1, "socket() ");
    sin->sin_family = AF_INET;
    sin->sin_port = 0;
    sin->sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(client->data_fd, (struct sockaddr *)(sin), sizeof(*sin));
    raise_error(ret != -1, "bind() ");
    ret = listen(client->data_fd, 1);
    raise_error(ret != -1, "listen() ");
    memset(sin, 0, sizeof(struct sockaddr_in));
    size = sizeof(*sin);
    getsockname(client->data_fd, (struct sockaddr *)(sin), &size);
}

static char *format_ip(char *given_ip)
{
    int i = 0;

    while (given_ip[i] != '\0') {
        if (given_ip[i] == '.')
            given_ip[i] = ',';
        i++;
    }
    return (given_ip);
}

void pasv(client_t *client, char *data UNUSED)
{
    struct sockaddr_in sin = { 0 };
    char prt_form[] = "227 Entering Passive Mode (%s,%u,%u).\r\n";
    char *ip;
    uint16_t port;

    init_socket(client, &sin);
    ip = format_ip(inet_ntoa(client->client_info.sin_addr));
    port = ntohs(sin.sin_port);
    dprintf(client->fd, prt_form, ip, port / 256, port % 256);
    client->mode = PASSIVE;
}