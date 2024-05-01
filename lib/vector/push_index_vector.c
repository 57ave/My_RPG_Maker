/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** push index vector
*/

#include "vector.h"
#include "my_lib.h"
#include <stdlib.h>

static void fill_null_data(vec_t *vec, size_t index)
{
    void **tmp_data = (void **)vec->data;

    if (index <= vec->size) {
        return;
    }
    for (size_t i = vec->size; i < index; i++) {
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
        vec->data = my_realloc(vec->data, vec->elem_size * (vec->capacity * 2)
        , vec->elem_size * vec->capacity);
        if (vec->data == NULL) {
            return NULL;
        }
        vec->capacity *= 2;
    }
    fill_null_data(vec, index);
    vec->size = (vec->size > index) ? vec->size : index;
    tmp_data = (void **)vec->data;
    tmp_data[index] = data;
    return vec;
}
