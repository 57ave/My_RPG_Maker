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
    #include "floor/floor_struct.h"

void pick_system(entity_system_t *es);
void draw_entities(entity_system_t *es, sfRenderWindow *wnd);
void draw_floor(sfRenderWindow *wnd, floor_t ***floor);
void move_entities(entity_system_t *es, floor_t ***);
bool interaction_zone_entities(entity_system_t *es, int index);
void aggro_entities(entity_system_t *es);
void warp_entities(entity_system_t *es);
void random_move_entities(entity_system_t *es);
void animation_system(entity_system_t *es);
bool collision_entities(entity_system_t *es, int e_1, int e_2);
void dialogue_system(entity_system_t *es, sfRenderWindow *wnd);
void damage_entities(entity_system_t *es, int entity1, int entity2);
void life_entities(entity_system_t *es, sfRenderWindow *wnd);
