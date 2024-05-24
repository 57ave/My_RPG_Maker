/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** up
*/

#include "components.h"
#include "ecs.h"
#include "macro.h"

int left_action(void *es)
{
    c_velocity_t *player_vel = get_comp((entity_system_t *)es,
    VELOCITY, ((entity_system_t *)es)->player);
    sfInt64 time = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(player_vel->clock)));

    player_vel->speed.x -=
        (time * player_vel->velocity.x) / 100000;
    return EXIT_SUCCESS;
}
