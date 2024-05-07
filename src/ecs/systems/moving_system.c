/*
** EPITECH PROJECT, 2024
** moving system
** File description:
** moving system
*/

#include <SFML/System.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"

static void reset_speed_entities(c_velocity_t *velocity_entity)
{
    velocity_entity->speed.x = 0;
    velocity_entity->speed.y = 0;
    sfClock_restart(velocity_entity->clock);
}

void move_entities(entity_system_t *es)
{
    entity_filter_t *filter = filter_entities(2, es, VELOCITY, POSITION);
    vec_t *component_pos = (vec_t *)(es->components[POSITION]);
    vec_t *component_vel = (vec_t *)(es->components[VELOCITY]);
    c_position_t *tmp_pos = NULL;
    c_velocity_t *tmp_vel = NULL;

    for (int i = 0; i < filter->number; ++i) {
        tmp_pos = (c_position_t *)
            ((void **)component_pos->data)[filter->indexes[i]];
        tmp_vel = (c_velocity_t *)
            ((void **)component_vel->data)[filter->indexes[i]];
        tmp_pos->pos.x += tmp_vel->speed.x;
        tmp_pos->pos.y += tmp_vel->speed.y;
        reset_speed_entities(tmp_vel);
    }
    free_filter(filter);
}
