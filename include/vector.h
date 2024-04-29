/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** vector
*/

#pragma once

    #include <stddef.h>

typedef struct vector {
    void *data;
    size_t elem_size;
    size_t capacity;
    size_t size;
} vec_t;

vec_t *init_vector(vec_t *vec, size_t size);

vec_t *push_back_vector(vec_t *vec, void *data, size_t data_size);

vec_t *push_index_vector(
    vec_t *vec, void *data, size_t data_size, size_t index
);
