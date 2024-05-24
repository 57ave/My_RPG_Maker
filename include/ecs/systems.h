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
bool interaction_zone_entities(entity_system_t *es, int entity1, int entity2);
void aggro_entities(entity_system_t *es);
void warp_entities(entity_system_t *es);
void random_move_entities(entity_system_t *es);
void animation_system(entity_system_t *es);
bool collision_entities(entity_system_t *es, int e_1, int e_2);
void dialogue_system(entity_system_t *es, sfRenderWindow *wnd);
void damage_entities(entity_system_t *es, int entity1, int entity2);
void life_entities(entity_system_t *es, sfRenderWindow *wnd);
int init_spell(entity_system_t *es, int item_inventory, int entity);
void spell_entities(entity_system_t *es);
int obj_to_components(entity_system_t *es, obj_t *obj, int entity);
void aggro_spell_system(entity_system_t *es, int entity, int target_entity);
void get_object_values(char **content, int *line_offset, obj_t *obj);
int set_vector_size(entity_system_t *es, int index);
bool temporary_system(entity_system_t *es, int entity);
void random_spell_move_system(entity_system_t *es, int entity);
