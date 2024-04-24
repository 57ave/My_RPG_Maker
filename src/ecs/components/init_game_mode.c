/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** game_mode
*/

#include "macro.h"
#include "my_toml.h"
#include "components.h"

int init_component_game_mode(entity_system_t *es, obj_t *obj,
    component_t type, int entity)
{
    c_game_mode_t *game_mode = calloc(sizeof(c_game_mode_t));
    int *mode = (int *)pull_data(obj, "GAME_MODE-MODE");
    if (!mode || !game_mode) {
        return EXIT_ERROR;
    }
    game_mode->mode = *mode;
    if (init_components(es, (void *)game_mode, type, entity) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
