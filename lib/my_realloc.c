/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_realloc
*/

#include "my_lib.h"
#include <stddef.h>
#include <stdlib.h>

void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr = NULL;

    if (ptr == NULL || old_size == 0) {
        return my_calloc(new_size);
    }
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = my_calloc(new_size);
    new_ptr = my_memcpy(new_ptr, ptr, new_size, old_size);
    free(ptr);
    return new_ptr;
}
