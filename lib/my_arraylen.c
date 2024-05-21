/*
** EPITECH PROJECT, 2024
** my arraylen
** File description:
** array len
*/

#include <unistd.h>

int my_arraylen(char **array)
{
    int i;

    for (i = 0; array[i] != NULL; i++);
    return i;
}
