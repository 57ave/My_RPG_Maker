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

struct entity_system {
    vec_t *entity_state;
    vec_t *components;
};

#endif /* !ECS_H_ */
