/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_vector
*/

#include "vector.h"
#include <stdlib.h>

vec_t *init_vector(vec_t *new_vec, size_t type_size)
{
    new_vec->data = malloc(type_size);
    if (new_vec->data == NULL) {
        return NULL;
    }
    new_vec->elem_size = type_size;
    new_vec->size = 0;
    new_vec->capacity = 1;
    return new_vec;
}
