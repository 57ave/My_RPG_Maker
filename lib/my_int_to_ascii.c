/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_int_to_ascii
*/

#include <stdlib.h>

int my_intlen(int nb)
{
    int len = 0;

    if (nb == 0) {
        return 1;
    }
    while (nb >= 1) {
        nb /= 10;
        len++;
    }
    return len;
}

char *int_to_ascii(int nb)
{
    int len = my_intlen(nb);
    char *str = malloc(sizeof(char) * (len + 1));
    int i = 1;

    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    for (; i <= len; i++) {
        str[len - i] = (nb % 10) + '0';
        nb /= 10;
    }
    str[i - 1] = '\0';
    return str;
}
