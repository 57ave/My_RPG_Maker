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
    if (line[*idx] == STRING_CHAR) {
        *idx += 1;
        return CHAR_PTR;
    }
    return -1;
}

char *get_value_string(char *line)
{
    char *value = my_strdup_delim(line, STRING_CHAR);

    if (value == NULL) {
        return NULL;
    }
    return value;
}
