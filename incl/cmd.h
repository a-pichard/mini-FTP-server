/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd
*/

#ifndef CMD_H_
#define CMD_H_

#include "server.h"

typedef void (*log_f_t)(const char *, client_t *, user_t *, int);

// utils
void auth(client_t *, user_t *, int);

// cmds
void user(const char *, client_t *, user_t *, int);
void pass(const char *, client_t *, user_t *, int);
void quit(server_t *, int);

#endif /* !CMD_H_ */