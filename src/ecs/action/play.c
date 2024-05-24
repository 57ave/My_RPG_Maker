/*
** EPITECH PROJECT, 2024
** play
** File description:
** play button
*/

#include "ecs.h"
#include "components.h"

void play(void *es)
{
    entity_system_t *esys = (entity_system_t *)es;

    esys->game_mode = ((c_game_mode_t *)
        get_comp(esys, GAME_MODE, esys->player))->mode;
}
