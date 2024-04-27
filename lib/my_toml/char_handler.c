/*
** EPITECH PROJECT, 2024
** my_toml
** File description:
** char handler
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stdlib.h>

int get_type_string(char *line, int *idx)
{
    if (line[*idx] == '"') {
        *idx += 1;
        return CHAR_PTR;
    }
    return EXIT_ERROR;
}

char *get_value_string(char *line)
{
    char *value = my_strdup_delim(line, STRING_CHAR);

    if (value == NULL) {
        return NULL;
    }
    return value;
}
