/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd
*/

#ifndef CMD_H_
#define CMD_H_

#include "server.h"

void auth(client_t *, user_t *, int);

void user(const char *, client_t *, user_t *, int);
void pass(const char *, client_t *, user_t *, int);

#endif /* !CMD_H_ */