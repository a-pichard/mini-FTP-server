/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "errors.h"
#include "server.h"
#include <stdlib.h>
#include <signal.h>

static void sig_handler(int sig UNUSED)
{
    destroy_server();
    exit(0);
}

int main(int ac, char **av)
{
    server_t serv = { 0 };

    signal(SIGINT, &sig_handler);
    input_error_handling(ac, av);
    init_server(&serv, atoi(av[1]), av[2], ac == 4);
    run_server(&serv);
    return (0);
}