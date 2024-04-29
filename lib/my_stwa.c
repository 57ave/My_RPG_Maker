/*
** EPITECH PROJECT, 2024
** pokemon
** File description:
** my_stwa
*/

#include <stdlib.h>
#include <string.h>

char **my_stwa(char *src, char *bad_char)
{
    int size = 1;
    int idx = 0;
    char **array = malloc(sizeof(char *) * (size + 1));
    char *token = strtok(src, bad_char);

    array[idx] = strdup(token);
    while (token != NULL) {
        size += 1;
        idx += 1;
        array = (char **)realloc(array, sizeof(char *) * (size + 1));
        if (array == NULL)
            return NULL;
        token = strtok(NULL, bad_char);
        if (token == NULL)
            break;
        array[idx] = strdup(token);
    }
    array[idx] = NULL;
    return array;
}
