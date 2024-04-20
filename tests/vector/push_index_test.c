/*
** EPITECH PROJECT, 2024
** vector
** File description:
** push_index_test
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "vector.h"

Test(push_index_vector, successful) {
    vec_t vec;
    void **data_tab = NULL;
    int data = 123;

    init_vector(&vec, sizeof(int));
    vec_t *result = push_index_vector(&vec, &data, sizeof(data), 1);
    cr_assert_not_null(result, "Vector is NULL after index push.");
    cr_assert(vec.size == 1, "Vector size incorrect after index push.");
    data_tab = (void **)vec.data;
    cr_assert(*(int *)(data_tab[1]) == 123, "Data not correctly added at index.");
    free(vec.data);
}

Test(push_index_vector, needs_resize) {
    vec_t vec;
    int data = 123;
    vec.data = malloc(sizeof(int));
    vec.elem_size = sizeof(int);
    vec.size = 1;
    vec.capacity = 1;

    vec_t *result = push_index_vector(&vec, &data, sizeof(data), 2);
    cr_assert_not_null(result, "Vector is NULL after resize for index.");
    cr_assert(vec.capacity > 2, "Vector capacity insufficient after resize.");
    free(vec.data);
}

Test(push_index_vector, fail_wrong_size) {
    vec_t vec;
    double data = 123.456;
    vec.data = malloc(sizeof(int));
    vec.elem_size = sizeof(int);
    vec.size = 0;
    vec.capacity = 1;

    vec_t *result = push_index_vector(&vec, &data, sizeof(data), 0);
    cr_assert_null(result, "Vector should be NULL due to wrong data size.");
    free(vec.data);
}
