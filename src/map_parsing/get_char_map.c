/*
** EPITECH PROJECT, 2024
** get char map
** File description:
** get char map
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.h>
#include "my_lib.h"

char **get_char_map(char const *const path)
{
    char *buffer = get_buffer(path);

    if (buffer == NULL)
        return NULL;
    return format_line(buffer, "\n", "");
}
