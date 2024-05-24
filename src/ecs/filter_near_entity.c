/*
** EPITECH PROJECT, 2024
** filter near entity
** File description:
** filter
*/

#include <stdbool.h>
#include <stdlib.h>
#include "ecs.h"
#include "position_component.h"
#include "components.h"
#include "macro.h"

static bool is_entity_nearby(entity_system_t *es, int entity,
    c_position_t *tmp, c_position_t *entity_pos)
{
    c_interaction_zone_t *entity_zone = get_comp(es, INTERACTION_ZONE, entity);

    if (ABS(tmp->pos.x - entity_pos->pos.x) < entity_zone->radius &&
        ABS(tmp->pos.y - entity_pos->pos.y) < entity_zone->radius) {
        return true;
    }
    return false;
}

static bool insert_entity(int index, int **entities,
    int *count)
{
    *entities = realloc(*entities, (sizeof(int)) *
        (*count + 1));
    if (*entities == NULL)
        return false;
    (*entities)[*count] = index;
    *count += 1;
    return true;
}

int *get_near_entities(entity_system_t *es, int entity, int *count)
{
    int *entities = NULL;
    c_position_t *tmp = NULL;
    c_position_t *entity_pos = get_comp(es, POSITION, entity);

    for (int i = 0; i < es->total_indexes; ++i) {
        tmp = (c_position_t *)get_comp(es, POSITION, es->all_indexes[i]);
        if ((tmp == NULL || is_entity_nearby(es, entity, tmp, entity_pos)) &&
            !insert_entity(i, &entities, count))
            return NULL;
    }
    return entities;
}
