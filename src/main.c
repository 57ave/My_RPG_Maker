/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** main
*/

#include "macro.h"
#include "launcher.h"

int main(int, char **, char **env)
{
    if (launcher(env) == EXIT_ERROR) {
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}
