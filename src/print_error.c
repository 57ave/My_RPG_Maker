/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** print_error
*/

#include <stdio.h>
#include "macro.h"

int print_error(char *error_mess, char *dynamic_name)
{
    if (!dynamic_name) {
        dprintf(2, error_mess, dynamic_name);
    } else {
        dprintf(2, error_mess);
    }
    return EXIT_ERROR;
}
