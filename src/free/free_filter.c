/*
** EPITECH PROJECT, 2024
** free_filtee
** File description:
** free the entity filters
*/

#include <stdlib.h>
#include "filter_entity.h"

void free_filter(entity_filter_t *filter)
{
    free(filter->indexes);
    free(filter);
}
