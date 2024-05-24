/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** inventory
*/

#include "components.h"
#include "ecs.h"
#include "macro.h"

int inventory_action(void *es)
{
    entity_system_t *ent_sys = (entity_system_t *)es;

    ent_sys->game_mode = (ent_sys->game_mode == 1) ? 2 : 1;
    return EXIT_SUCCESS;
}
