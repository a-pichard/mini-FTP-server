/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** error
*/

#ifndef ERROR_H_
#define ERROR_H_

#include <stdbool.h>

void helper(const char *, int);
void input_error_handling(int, char **);
void raise_error(bool, const char *);

#endif /* !ERROR_H_ */