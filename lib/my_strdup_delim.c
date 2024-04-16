/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "my_lib.h"
#include <stddef.h>

size_t my_len_to_delim(char *str, char delim)
{
    size_t len = 0;

    while (str[len] != '\0') {
        if (str[len + 1] == delim) {
            return len + 1;
        }
        len++;
    }
    return len;
}

char *my_strdup_delim(char *str, char delim)
{
    char *new_str = malloc(sizeof(char) * (my_len_to_delim(str, delim) + 1));
    int i = 0;

    if (new_str == NULL)
        return NULL;
    for (i = 0; str[i] != delim && str[i] != '\0'; i++) {
        new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}
