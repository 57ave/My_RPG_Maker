/*
** EPITECH PROJECT, 2024
** my_toml
** File description:
** char handler
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stdbool.h>
#include <stdlib.h>

int get_type_string(char *line, int *idx)
{
    if (line[*idx] == STRING_CHAR) {
        *idx += 1;
        return CHAR_PTR;
    }
    return -1;
}

static bool check_delim(char *str, int i)
{
    if (str[i] != '"') {
        if (i > 0 && str[i - 1] == '\\') {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

static int my_len_of_str(char *str)
{
    int i = 0;

    for (i = 0; check_delim(str, i) && str[i] != '\0'; i++);
    return i;
}

static char *my_get_string_value(char *str)
{
    int len = my_len_of_str(str);
    char *new_str = NULL;
    int i = 0;

    if (len < 0)
        return NULL;
    new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
        return NULL;
    for (i = 0; check_delim(str, i) && str[i] != '\0'; i++) {
        new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}

char *get_value_string(char *line)
{
    char *value = my_get_string_value(line);

    if (value == NULL) {
        return NULL;
    }
    return value;
}
