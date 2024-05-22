/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** heatlh_component.h
*/

#pragma once

#include <SFML/System/Clock.h>

typedef struct health_s {
    int current_health;
    int max_health;
    int current_armor;
    int max_armor;
    sfClock *clock;
} c_health_t;
