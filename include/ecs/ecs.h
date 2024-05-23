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

typedef struct entity_system_s {
    int player;
    int *entity_indexes;
    int nb_of_entities;
    vec_t **components;
    gamemode_keys_t keys[3];
} entity_system_t;

#endif
