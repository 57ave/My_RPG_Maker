/*
** EPITECH PROJECT, 2024
** vector
** File description:
** init_test
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdlib.h>
#include "vector.h"

Test(init_vector, successful_initialization) {
    vec_t vec;
    size_t elem_size = sizeof(int);

    vec_t *result = init_vector(&vec, elem_size);
    cr_assert_not_null(result, "Vector is NULL after initialization.");
    cr_assert_not_null(vec.data, "Data pointer is NULL after initialization.");
    cr_assert_eq(vec.elem_size, elem_size, "Element size not set correctly.");
    cr_assert_eq(vec.size, 0, "Initial size is not zero.");
    cr_assert_eq(vec.capacity, 1, "Initial capacity is not one.");
    free(vec.data);
}

Test(init_vector, fail_initialization) {
    vec_t vec;

    vec_t *result = init_vector(&vec, -1);
    cr_assert_null(result, "Vector should be NULL due to failed malloc.");
}
