/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "errors.h"
#include "server.h"
#include <stdlib.h>

int main(int ac, char **av)
{
    server_t serv = { 0 };

    input_error_handling(ac, av);
    init_server(&serv, atoi(av[1]), av[2]);
    // do stuff
    destroy_server(&serv);
    return (0);
}