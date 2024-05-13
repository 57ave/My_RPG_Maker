/*
** EPITECH PROJECT, 2024
** system_loop
** File description:
** system_loop.c
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "components.h"
#include "macro.h"
#include "launcher.h"
#include "vector.h"
#include "ecs.h"
#include "filter_entity.h"
#include "systems.h"

static void catch_keys(entity_system_t *es)
{
    c_velocity_t *player_velocity = (c_velocity_t *)
        (((void **)(((vec_t *)
        (es->components[VELOCITY]))->data))[es->player]);
    sfInt64 time = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(player_velocity->clock)));

    if (sfKeyboard_isKeyPressed(sfKeyD))
        player_velocity->speed.x +=
            (time * player_velocity->velocity.x) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        player_velocity->speed.x -=
            (time * player_velocity->velocity.x) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        player_velocity->speed.y -=
            (time * player_velocity->velocity.y) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        player_velocity->speed.y +=
            (time * player_velocity->velocity.y) / 100000;
    sfClock_restart(player_velocity->clock);
}

void system_loop(sfRenderWindow *wnd, entity_system_t *es)
{
    catch_keys(es);
    aggro_entities(es);
    random_move_entities(es);
    move_entities(es);
    draw_entities(es, wnd);
}
