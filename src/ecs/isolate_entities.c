/*
** EPITECH PROJECT, 2024
** isolate entities
** File description:
** isolate entities with a component filter
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"
#include "ecs.h"
#include "filter_entity.h"

static size_t *get_filters(va_list ap, size_t nb_of_filters)
{
    size_t *filters = calloc(sizeof(size_t), nb_of_filters);

    if (filters == NULL)
        return NULL;
    for (size_t i = 0; i < nb_of_filters; ++i) {
        filters[i] = va_arg(ap, size_t);
    }
    return filters;
}

static bool check_components(entity_system_t *es,
    size_t *filters, size_t nb_of_filters, int index)
{
    vec_t *component = NULL;

    for (size_t i = 0; i < nb_of_filters; ++i) {
        component = es->components[filters[i]];
        if (((void **)(component->data))[index] == NULL)
            return false;
    }
    return true;
}

static entity_filter_t *filter_indexes(entity_system_t *es,
    size_t *filters, size_t nb_of_filters)
{
    entity_filter_t *filter = calloc(sizeof(entity_filter_t), 1);

    if (filter == NULL)
        return NULL;
    for (int i = 0; i < es->nb_of_entities; ++i) {
        if (!check_components(es, filters, nb_of_filters,
            es->entity_indexes[i]))
            continue;
        filter->indexes = realloc(filter->indexes,
            sizeof(int) * (filter->number + 1));
        if (filter->indexes == NULL) {
            free(filter);
            free(filters);
            return NULL;
        }
        filter->indexes[filter->number] = es->entity_indexes[i];
        filter->number += 1;
    }
    free(filters);
    return filter;
}

entity_filter_t *filter_entities(size_t nb_of_filters,
    entity_system_t *es, ...)
{
    va_list ap;
    size_t *filters = NULL;

    va_start(ap, es);
    filters = get_filters(ap, nb_of_filters);
    if (filters == NULL)
        return NULL;
    return filter_indexes(es, filters, nb_of_filters);
}
