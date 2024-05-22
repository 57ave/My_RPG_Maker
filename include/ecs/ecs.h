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

typedef struct entity_system {
    int player;
    int *all_indexes;
    int total_indexes;
    int game_mode;
    int *entity_indexes;
    int nb_of_entities;
    vec_t **components;
}entity_system_t;

#endif
