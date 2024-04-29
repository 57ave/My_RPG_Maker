/*
** EPITECH PROJECT, 2023
** toml_parser
** File description:
** open_toml
*/

#include "my_lib.h"
#include <stdio.h>
#include <unistd.h>

char **read_file(char const *filepath)
{
    FILE *file_ptr = fopen(filepath, "r");
    char *lineptr = NULL;
    char **content = NULL;
    size_t size_read = 0;
    size_t n = 0;
    int nb_line = 1;

    if (file_ptr == NULL) {
        return NULL;
    }
    for (; getline(&lineptr, &n, file_ptr) > 0; nb_line++) {
        size_read += n;
        content = my_realloc(
        content, sizeof(char *) * (nb_line + 1), sizeof(char *) * nb_line);
        content[nb_line - 1] = my_strdup(lineptr);
    }
    content[nb_line - 1] = NULL;
    fclose(file_ptr);
    return content;
}
