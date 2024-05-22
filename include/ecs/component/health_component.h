/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** heatlh_component.h
*/

#pragma once

#include <SFML/System/Clock.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>

typedef struct health_s {
    int current_health;
    int max_health;
    int current_armor;
    int max_armor;
    sfRectangleShape *health_rect;
    sfRectangleShape *armor_rect;
    sfVector2f life_bar_size;
    sfClock *clock;
} c_health_t;
