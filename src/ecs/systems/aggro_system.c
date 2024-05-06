/*
** EPITECH PROJECT, 2024
** aggro_system
** File description:
** aggro_system
*/

#include <SFML/System.h>
#include <math.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void aggro_move_direction(entity_system_t *es,
    c_velocity_t *entity_vel, c_position_t *entity_pos)
{
    c_position_t *player_pos = (c_position_t *)
        (((void **)(((vec_t *)
        (es->components[POSITION]))->data))[es->player]);
    sfInt64 time = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(entity_vel->clock)));
    float vector_x = player_pos->pos.x - entity_pos->pos.x;
    float vector_y = player_pos->pos.y - entity_pos->pos.y;
    float u_value = sqrtf(pow(vector_x, 2.0) + pow(vector_y, 2.0));

    if (u_value == 0 || (vector_x < 3.0 && vector_x > -3.0
    && vector_y > -3.0 && vector_y < 3.0))
        return;
    entity_vel->speed.x = vector_x / u_value *
        ((time * entity_vel->velocity.x) / 100000);
    entity_vel->speed.y = vector_y / u_value *
        ((time * entity_vel->velocity.y) / 100000);
}

static void reset_entities_velocity(c_velocity_t *velocity_entity)
{
    velocity_entity->speed.x = 0;
    velocity_entity->speed.y = 0;
    sfClock_restart(velocity_entity->clock);
}

void aggro_entities(entity_system_t *es)
{
    entity_filter_t *filter = filter_entities(4, es, VELOCITY, POSITION,
    DAMAGE, INTERACTION_ZONE);
    vec_t *component_pos = (vec_t *)(es->components[POSITION]);
    vec_t *component_vel = (vec_t *)(es->components[VELOCITY]);
    c_position_t *tmp_pos = NULL;
    c_velocity_t *tmp_vel = NULL;

    for (int i = 0; i < filter->number; ++i) {
        tmp_vel = (c_velocity_t *)
            ((void **)component_vel->data)[filter->indexes[i]];
        if (interaction_zone_entities(es, filter->indexes[i])) {
            tmp_pos = (c_position_t *)
                ((void **)component_pos->data)[filter->indexes[i]];
            aggro_move_direction(es, tmp_vel, tmp_pos);
            tmp_pos->pos.x += tmp_vel->speed.x;
            tmp_pos->pos.y += tmp_vel->speed.y;
        }
        reset_entities_velocity(tmp_vel);
    }
    free_filter(filter);
}
