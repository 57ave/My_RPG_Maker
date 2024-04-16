/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "my_lib.h"

char *my_strdup(char const *str)
{
    char *new_str = malloc(sizeof(char) * my_strlen((char *)str) + 1);
    int i = 0;

    if (new_str == NULL) {
        return NULL;
    }
    for (; str[i] != '\0'; i++) {
        new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}
