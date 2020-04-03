/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd
*/

#ifndef CMD_H_
#define CMD_H_

#include "server.h"

// index of functions pointer
typedef void (*log_f_t)(const char *, client_t *, user_t *, int);
typedef void (*cmd_t)(client_t *, const char *);

// utils
void auth(client_t *, user_t *, int);

// cmds
void user(const char *, client_t *, user_t *, int);
void pass(const char *, client_t *, user_t *, int);
void quit(server_t *, int);
void pwd(client_t *, const char *);
void noop(client_t *, const char *);
void pasv(client_t *, const char *);

#endif /* !CMD_H_ */