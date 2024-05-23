/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** ecs
*/

#ifndef ECS_H_
    #define ECS_H_

    #include <stddef.h>
    #include "vector.h"
    #include "key_mapping.h"

    #define GAMEMODE_COUNT 12

typedef struct entity_system_s {
    int player;
    int *entity_indexes;
    int nb_of_entities;
    vec_t **components;
    int game_mode;
    gamemode_keys_t keys[GAMEMODE_COUNT];
} entity_system_t;

#endif
