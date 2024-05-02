/*
** EPITECH PROJECT, 2024
** systems
** File description:
** systems
*/

#pragma once

    #include <SFML/Graphics.h>
    #include "ecs.h"

void draw_entities(entity_system_t *es, sfRenderWindow *wnd);
void move_entities(entity_system_t *es);
