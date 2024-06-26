/*
** EPITECH PROJECT, 2024
** interaction_zone_system
** File description:
** interaction_zone_system
*/

#include <math.h>
#include <stdbool.h>
#include "ecs.h"
#include "components.h"

static bool is_inside_zone(sfVector2f *point, sfVector2f *center,
    int radius)
{
    float distance = 0.0;

    distance = sqrtf(pow(point->x - center->x, 2.0) +
    pow(point->y - center->y, 2.0));
    if (distance < radius)
        return true;
    return false;
}

bool interaction_zone_entities(entity_system_t *es, int entity1, int entity2)
{
    vec_t *component_zone = es->components[INTERACTION_ZONE];
    vec_t *component_pos = es->components[POSITION];
    c_position_t *tmp_pos1 = (c_position_t *)
        (((void **)(((vec_t *)
        (es->components[POSITION]))->data))[entity1]);
    c_position_t *tmp_pos2 = (c_position_t *)
        ((void **)component_pos->data)[entity2];
    c_interaction_zone_t *tmp_zone = (c_interaction_zone_t *)
        ((void **)component_zone->data)[entity2];

    if (!tmp_pos1 || !tmp_pos2 || !tmp_zone)
        return false;
    if (is_inside_zone(&tmp_pos1->pos, &tmp_pos2->pos,
        tmp_zone->radius))
        return true;
    return false;
}
