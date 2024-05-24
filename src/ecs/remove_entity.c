/*
** EPITECH PROJECT, 2024
** remove_entity
** File description:
** remove_entity
*/

#include <stdbool.h>
#include <stdlib.h>
#include "ecs.h"
#include "position_component.h"
#include "components.h"
#include "macro.h"

int remove_entity(entity_system_t *es, int entity)
{
    int *total = malloc(sizeof(int) * (es->total_indexes - 1));
    int j = 0;

    if (!total)
        return EXIT_ERROR;
    for (int i = 0; i < es->total_indexes - 1; ++i) {
        if (entity == es->all_indexes[i])
            continue;
        total[j] = es->all_indexes[i];
        ++j;
    }
    free(es->all_indexes);
    --es->total_indexes;
    es->all_indexes = total;
    return EXIT_SUCCESS;
}
