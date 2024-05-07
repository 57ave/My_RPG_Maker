/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** cat strings
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static void *free_stuff(char *result, va_list args)
{
    free(result);
    va_end(args);
    return NULL;
}

char *concat_strings(size_t num_args, ...)
{
    va_list args;
    char *result = calloc(1, 1);
    const char *str = NULL;
    size_t current_length = 0;
    size_t str_len = 0;

    va_start(args, num_args);
    if (!result)
        return NULL;
    for (size_t i = 0; i < num_args; i++) {
        str = va_arg(args, const char *);
        str_len = strlen(str);
        result = realloc(result, current_length + str_len + 1);
        if (!result)
            return free_stuff(result, args);
        strcat(result, str);
        current_length += str_len;
    }
    va_end(args);
    return result;
}
