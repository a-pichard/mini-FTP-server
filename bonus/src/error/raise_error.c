/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** raise_error
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void raise_error(bool err, const char *msg)
{
    if (!err) {
        perror(msg);
        exit(84);
    }
}