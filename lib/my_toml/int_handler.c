/*
** EPITECH PROJECT, 2023
** my_toml
** File description:
** int handler
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stdlib.h>

int get_type_int(char *line, int *idx)
{
    for (int i = 0; INT_CHARS[i] != '\0'; i++) {
        if (INT_CHARS[i] == line[*idx]) {
            return INT;
        }
    }
    return EXIT_ERROR;
}

void *get_value_int(char *line)
{
    int value = 0;
    int *ptr = NULL;

    value = my_getnbr(line);
    ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        return NULL;
    }
    *ptr = value;
    return (void *)ptr;
}
