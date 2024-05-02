/*
** EPITECH PROJECT, 2024
** filter entity
** File description:
** filter entity
*/

#pragma once

    #include <stdarg.h>
    #include <stddef.h>
    #include "ecs.h"

typedef struct entity_filter_s {
    int number;
    int *indexes;
}entity_filter_t;

entity_filter_t *filter_entities(size_t nb_of_filters,
    entity_system_t *es, ...);
void free_filter(entity_filter_t *filter);
