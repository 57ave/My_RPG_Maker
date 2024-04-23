/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** laucking error
*/

#include <stdlib.h>
#include "macro.h"

int env_verification(char **env)
{
    if (getenv("DISPLAY") == NULL) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
