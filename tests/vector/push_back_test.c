/*
** EPITECH PROJECT, 2024
** vector
** File description:
** push_back_test
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "vector.h"

Test(push_back_vector, successful) {
    vec_t vec;
    int data = 123;
    void **data_tab = NULL;

    init_vector(&vec, sizeof(int));
    vec_t *result = push_back_vector(&vec, &data, sizeof(data));
    cr_assert_not_null(result, "Vector is NULL after push_back.");
    cr_assert(vec.size == 1, "Vector size did not increase.");
    data_tab = (void **)vec.data;
    cr_assert(*(int *)data_tab[0] == 123, "Data not correctly added.");
    free(vec.data);
}

Test(push_back_vector, needs_resize) {
    vec_t vec;
    int data = 123;
    vec.data = malloc(sizeof(int));
    vec.elem_size = sizeof(int);
    vec.size = 1;
    vec.capacity = 1;

    vec_t *result = push_back_vector(&vec, &data, sizeof(data));
    cr_assert_not_null(result, "Vector is NULL after resize.");
    cr_assert(vec.capacity > 1, "Vector capacity was not increased.");
    cr_assert(vec.size == 2, "Vector size incorrect after resize.");
    free(vec.data);
}

Test(push_back_vector, fail_wrong_size) {
    vec_t vec ;
    double data = 123.456;

    init_vector(&vec, sizeof(int));
    vec_t *result = push_back_vector(&vec, &data, sizeof(data));
    cr_assert_null(result, "Vector should be NULL due to wrong data size.");
    free(vec.data);
}
