/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** port
*/

#include "server.h"
#include "errors.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

static int get_port(const char *data)
{
    int nb1 = 0;
    int nb2 = 0;
    int nb_sep = 0;
    int i = 0;

    for (; data[i] != '\0'; i++) {
        if (data[i] == ',') {
            nb1 = nb2;
            nb2 = 0;
            nb_sep++;
        } else if (data[i] >= '0' && data[i] <= '9') {
            nb2 = nb2 * 10 + (data[i] - 48);
        } else
            return (-1);
    }
    if (nb_sep != 1 || data[i - 1] == ',')
        return (-1);
    return (nb1 * 256 + nb2);
}

static bool parse_data(const char *data, char *ip, int *port)
{
    int nb_dot = 0;
    int i = 0;

    if (!data)
        return (false);
    for (; data[i] != '\0' && nb_dot < 4; i++) {
        if (data[i] == ',') {
            ip[i] = '.';
            nb_dot++;
        } else if (data[i] >= '0' && data[i] <= '9') {
            ip[i] = data[i];
        } else
            return (false);
    }
    if (nb_dot != 4 || data[i] == '\0')
        return (false);
    ip[i - 1] = '\0';
    if ((*port = get_port(&data[i])) == -1)
        return (false);
    return (true);
}

static bool fill_sin(const char *data, struct sockaddr_in *sin)
{
    char ip[16] = { 0 };
    int port;

    if (!data)
        return (false);
    if (!parse_data(data, ip, &port))
        return (false);
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(ip);
    return (true);
}

void port(client_t *client, const char *data)
{
    struct sockaddr_in sin = { 0 };
    int ret;

    if (!fill_sin(data, &sin)) {
        respond_to(client->fd, "500 Missing data connection.\r\n");
        return;
    }
    if (client->data_fd != -1)
        close(client->data_fd);
    client->data_fd = socket(AF_INET, SOCK_STREAM, 0);
    raise_error(client->data_fd != -1, "socket() ");
    ret = connect(client->data_fd, (struct sockaddr *)(&sin), sizeof(sin));
    if (ret == -1)
        respond_to(client->fd, "500 Failed to connect to socket.\r\n");
    else
        respond_to(client->fd, "200 Command okay.\r\n");
}