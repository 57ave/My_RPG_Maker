/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launch_rpg
*/

#include <stdlib.h>
#include "components.h"
#include "macro.h"
#include "launcher.h"

static int test(void)
{
    entity_system_t *tmp = calloc(sizeof(entity_system_t), 1);

    tmp->entity_state = calloc(sizeof(vec_t), 1);
    tmp->components = calloc(sizeof(vec_t), 1);
    if (init_entity_system(tmp) == NULL)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int launcher(char **env)
{
    if (env_verification(env) == EXIT_ERROR)
        return EXIT_ERROR;
    if (test() == EXIT_ERROR)
        return 42;
    return EXIT_SUCCESS;
}
