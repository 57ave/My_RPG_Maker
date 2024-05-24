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
    int *all_indexes;
    int total_indexes;
    int game_mode;
    int *entity_indexes;
    int nb_of_entities;
    int max_index;
    vec_t **components;
    gamemode_keys_t keys[GAMEMODE_COUNT];
} entity_system_t;

int read_keys_from_file(entity_system_t *es, const char *filepath);

#endif
