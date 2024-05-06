/*
** EPITECH PROJECT, 2024
** systems
** File description:
** systems
*/

#pragma once

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include "ecs.h"

void draw_entities(entity_system_t *es, sfRenderWindow *wnd);
void move_entities(entity_system_t *es);
bool interaction_zone_entities(entity_system_t *es, int index);
void aggro_entities(entity_system_t *es);
