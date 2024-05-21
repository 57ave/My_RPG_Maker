/*
** EPITECH PROJECT, 2024
** moving system
** File description:
** mooving system
*/

#include <SFML/System.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void move_entities_position(entity_system_t *es,
    int warp, entity_filter_t *to_warp)
{
    vec_t *component_pos = (vec_t *)(es->components[POSITION]);
    vec_t *component_warp = (vec_t *)(es->components[WARP]);
    c_position_t *to_warp_pos = NULL;
    c_warp_t *warp_coord = (c_warp_t *)
        ((void **)component_warp->data)[warp];

    for (int i = 0; i < to_warp->number; ++i) {
        if (collision_entities(es, warp, to_warp->indexes[i])) {
            to_warp_pos = (c_position_t *)
                ((void **)component_pos->data)[to_warp->indexes[i]];
            to_warp_pos->pos.x = warp_coord->warp.x;
            to_warp_pos->pos.y = warp_coord->warp.x;
        }
    }
}

void warp_entities(entity_system_t *es)
{
    entity_filter_t *filter =
        filter_entities(2, es, WARP, POSITION);
    entity_filter_t *to_warp =
        filter_entities(2, es, VELOCITY, POSITION);

    for (int i = 0; i < filter->number; ++i) {
        move_entities_position(es, filter->indexes[i], to_warp);
    }
    free_filter(filter);
}
