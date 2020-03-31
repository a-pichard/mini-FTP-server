/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** error
*/

#ifndef ERROR_H_
#define ERROR_H_

#include <stdbool.h>

void helper(int exit_status);
void input_error_handling(int ac, char **av);
void raise_error(bool err, const char *msg);

#endif /* !ERROR_H_ */