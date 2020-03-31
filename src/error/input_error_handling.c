/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** input_error_handling
*/

#include "error.h"
#include <string.h>
#include <unistd.h>

static bool isStrDigit(const char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

void input_error_handling(int ac, char **av)
{
    if (ac == 3) {
        if (!isStrDigit(av[1]))
            helper(84);
        if (access(av[2], F_OK | R_OK | W_OK) == -1)
            helper(84);
    } else if (ac == 2 && (!strcmp(av[1], "-help") || !strcmp(av[1], "-h")))
        helper(0);
    else
        helper(84);
}