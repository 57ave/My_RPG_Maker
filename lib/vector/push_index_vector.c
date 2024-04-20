/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** push index vector
*/

#include "vector.h"
#include "my_lib.h"
#include <stdlib.h>

vec_t *push_index_vector(
    vec_t *vec, void *data, size_t data_size, size_t index)
{
    void **tmp_data = NULL;

    if (data_size != vec->elem_size) {
        return NULL;
    }
    while (index >= vec->capacity) {
        vec->data = my_realloc(vec->data, vec->elem_size * (vec->capacity * 2)
        , vec->elem_size * vec->capacity);
        if (vec->data == NULL) {
            return NULL;
        }
        vec->capacity *= 2;
    }
    vec->size += 1;
    tmp_data = (void **)vec->data;
    tmp_data[index] = data;
    return vec;
}
