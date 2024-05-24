/*
** EPITECH PROJECT, 2024
** filter near player
** File description:
** filter
*/

#include <stdbool.h>
#include <stdlib.h>
#include "ecs.h"
#include "position_component.h"
#include "components.h"
#include "macro.h"

static bool is_entity_nearby(c_position_t *entity, c_position_t *player)
{
    if (ABS(entity->pos.x - player->pos.x) < FILTER_RANGE &&
        ABS(entity->pos.y - player->pos.y) < FILTER_RANGE) {
        return true;
    }
    return false;
}

static bool insert_entity(entity_system_t *es, int index)
{
    es->entity_indexes = realloc(es->entity_indexes, (sizeof(int)) *
        (es->nb_of_entities + 1));
    if (es->entity_indexes == NULL)
        return false;
    es->entity_indexes[es->nb_of_entities] = index;
    es->nb_of_entities += 1;
    return true;
}

bool get_entities(entity_system_t *es)
{
    c_position_t *tmp = NULL;
    c_position_t *player_pos = get_comp(es, POSITION, es->player);

    for (int i = 0; i < es->total_indexes; ++i) {
        tmp = (c_position_t *)get_comp(es, POSITION, es->all_indexes[i]);
        if ((tmp == NULL || is_entity_nearby(tmp, player_pos)) &&
            !insert_entity(es, i))
            return false;
    }
    return true;
}
