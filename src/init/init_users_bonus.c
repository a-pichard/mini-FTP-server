/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_users
*/

#include "server.h"
#include "errors.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static char *get_file(const char *path)
{
    char *file = NULL;
    struct stat st;
    int ret = stat(path, &st);
    int fd;
    size_t size;

    raise_error(ret == 0, "stat() ");
    size = st.st_size;
    file = malloc(sizeof(char) * (size + 1));
    raise_error(file != NULL, "malloc() ");
    fd = open(path, O_RDONLY);
    raise_error(fd != -1, "open() ");
    ret = read(fd, file, size);
    raise_error(ret > 0, "read() ");
    file[ret] = '\0';
    return (file);
}

static char **get_cutted_file(const char *path)
{
    char *unparsed = get_file(path);
    int nb_lines = 2;
    char **file = NULL;
    char *line;
    size_t j = 0;

    for (size_t i = 0; unparsed[i] != '\0'; i++) {
        if (unparsed[i] == '\0')
            nb_lines++;
    }
    file = malloc(sizeof(char *) * (nb_lines + 1));
    line = strtok(unparsed, "\n");
    while (line != NULL) {
        file[j] = strdup(line);
        line = strtok(NULL, "\n");
        j++;
    }
    file[j] = NULL;
    free(unparsed);
    return (file);
}

void init_users(server_t *s, const char *path_to_user_file)
{
    char **file = get_cutted_file(path_to_user_file);
    char *elem;

    for (s->nb_users = 0; file[s->nb_users] != NULL; s->nb_users++);
    s->users = malloc(sizeof(user_t) * (s->nb_users));
    for (size_t i = 0; file[i] != NULL; i++) {
        s->users[i].username = strdup(strtok(file[i], ":"));
        if (!strcmp((elem = strtok(NULL, ":")), "!"))
            s->users[i].password = strdup("");
        else
            s->users[i].password = strdup(elem);
        s->users[i].home = strdup(strtok(NULL, ":"));
        free(file[i]);
    }
    free(file);
}