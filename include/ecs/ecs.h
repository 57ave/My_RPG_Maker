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
    //vec_t *entity_state;
    int *entity_indexes;
    int nb_of_entities;
<<<<<<< HEAD
    vec_t **components;
}entity_system_t;
=======
    vec_t *components;
} entity_system_t;
>>>>>>> 95b89b8f42d192c6181bb6f82f93039de8284145

#endif
