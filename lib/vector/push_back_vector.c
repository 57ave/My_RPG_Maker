/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** push_back_vector
*/

#include <stdlib.h>
#include "vector.h"
#include "my_lib.h"

vec_t *push_back_vector(vec_t *vec, void *data, size_t data_size)
{
    void **tmp_data = NULL;

    if (data_size != vec->elem_size) {
        return NULL;
    }
    if (vec->size == vec->capacity) {
        vec->data = my_realloc(vec->data, vec->elem_size * (vec->capacity * 2)
        , vec->elem_size * vec->capacity);
        if (vec->data == NULL) {
            return NULL;
        }
    }
    tmp_data = (void **)vec->data;
    tmp_data[vec->size] = data;
    vec->size++;
    vec->capacity *= 2;
    return vec;
}
