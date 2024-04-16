/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_strlen
*/

#include <stddef.h>

size_t my_strlen(char *str)
{
    size_t size = 0;

    while (str[size] != '\0') {
        size++;
    }
    return size;
}
