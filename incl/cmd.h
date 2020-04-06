/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cmd
*/

#ifndef CMD_H_
#define CMD_H_

#include "server.h"

#define F_NAME {"PWD",  \
    "NOOP", \
    "PASV", \
    "PORT", \
    "RETR", \
    "CWD",  \
    "CDUP", \
    "LIST", \
    NULL    \
};

#define F_FUNC {&pwd,   \
    &noop,  \
    &pasv,  \
    &port,  \
    &retr,  \
    &cwd,   \
    &cdup,  \
    &list   \
}

#define TIMEOUT_IN_SEC 15

// index of functions pointer
typedef void (*log_f_t)(char *, client_t *, user_t *, int);
typedef void (*cmd_t)(client_t *, char *);

// utils
void auth(client_t *, user_t *, int);
char *get_path(const char *, const char *, const char *);
char *get_relative_path(const char *, const char *);
bool write_in_fork(int, void *, size_t);
int accept_connection(int);

// cmds
void user(char *, client_t *, user_t *, int);
void pass(char *, client_t *, user_t *, int);
void quit(client_t *);
void pwd(client_t *, char *);
void noop(client_t *, char *);
void pasv(client_t *, char *);
void port(client_t *, char *);
void retr(client_t *, char *);
void cwd(client_t *, char *);
void cdup(client_t *, char *);
void list(client_t *, char *);

#endif /* !CMD_H_ */