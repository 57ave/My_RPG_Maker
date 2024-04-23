/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launch_rpg
*/

#include <stdlib.h>
#include "macro.h"
#include "launcher.h"

int launcher(char **env)
{
    if (env_verification(env) == EXIT_SUCCESS)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
