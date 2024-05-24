/*
** EPITECH PROJECT, 2024
** aggro_spell_system
** File description:
** aggro_spell_system
*/

#include <SFML/System.h>
#include <math.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void reset_target(entity_system_t *es, c_position_t *entity_pos,
    int entity)
{
    vec_t *component_zone = es->components[INTERACTION_ZONE];
    c_interaction_zone_t *tmp_zone = (c_interaction_zone_t *)
        ((void **)component_zone->data)[entity];

    tmp_zone->target_position.x = entity_pos->pos.x;
    tmp_zone->target_position.y = entity_pos->pos.y;
}

void aggro_spell_system(entity_system_t *es, int entity, int target_entity)
{
    c_velocity_t *entity_vel = get_comp(es, VELOCITY, entity);
    c_position_t *entity_pos = get_comp(es, POSITION, entity);
    c_position_t *target_pos = get_comp(es, POSITION, target_entity);
    sfInt64 time = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(entity_vel->clock)));
    float vector_x = target_pos->pos.x - entity_pos->pos.x;
    float vector_y = target_pos->pos.y - entity_pos->pos.y;
    float u_value = sqrtf(pow(vector_x, 2.0) + pow(vector_y, 2.0));

    if (u_value == 0 || (vector_x < 3.0 && vector_x > -3.0
    && vector_y > -3.0 && vector_y < 3.0))
        return;
    entity_vel->speed.x = vector_x / u_value *
        ((time * entity_vel->velocity.x) / 100000);
    entity_vel->speed.y = vector_y / u_value *
        ((time * entity_vel->velocity.y) / 100000);
    reset_target(es, entity_pos, entity);
}
