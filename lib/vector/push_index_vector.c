/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** push index vector
*/

#include "vector.h"
#include "my_lib.h"
#include <stdlib.h>

static void fill_null_data(vec_t *vec)
{
    void **tmp_data = (void **)vec->data;

    for (size_t i = vec->capacity; i < (vec->capacity * 2); i++) {
        tmp_data[i] = NULL;
    }
}

vec_t *push_index_vector(
    vec_t *vec, void *data, size_t data_size, size_t index)
{
    void **tmp_data = NULL;

    if (data_size != vec->elem_size) {
        return NULL;
    }
    while (index >= vec->capacity) {
        vec->data = realloc(vec->data, vec->elem_size * (vec->capacity * 2));
        if (vec->data == NULL) {
            return NULL;
        }
        fill_null_data(vec);
        vec->capacity *= 2;
    }
    vec->size = (vec->size > index) ? vec->size : index;
    tmp_data = (void **)vec->data;
    tmp_data[index] = data;
    return vec;
}
