/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_calloc
*/

#include <stdlib.h>
#include "my_lib.h"

void *my_calloc(size_t size)
{
    void *new_ptr = malloc(size);

    if (new_ptr == NULL) {
        return NULL;
    }
    new_ptr = my_memset(new_ptr, size);
    return new_ptr;
}
