/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** velocity_component.h
*/

#pragma once

#include <SFML/System/Vector2.h>
#include <SFML/System/Clock.h>

typedef struct velocity_s {
    sfVector2f velocity;
    sfVector2f speed;
    sfClock *clock;
    sfClock *floor_sound;
} c_velocity_t;
