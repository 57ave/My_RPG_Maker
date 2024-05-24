/*
** EPITECH PROJECT, 2024
** spell_component
** File description:
** spell_component
*/

#pragma once

#include <SFML/System/Clock.h>

typedef struct active_item_s {
    sfClock *clock;
    size_t time;
} c_active_item_t;
