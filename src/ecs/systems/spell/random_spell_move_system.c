/*
** EPITECH PROJECT, 2024
** randaom_spell_move_system
** File description:
** random_spell_move_system
*/

#include <SFML/System.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void init_random_direction(c_position_t *entity_pos,
    sfVector2f *target_position, c_interaction_zone_t *tmp_zone)
{
    if (rand() % 2 == 0)
        target_position->x = entity_pos->pos.x + (rand() % 200) + 1;
    else
        target_position->x = entity_pos->pos.x - (rand() % 200) - 1;
    if (rand() % 2 == 0)
        target_position->y = entity_pos->pos.y + (rand() % 200) + 1;
    else
        target_position->y = entity_pos->pos.y - (rand() % 200) - 1;
    tmp_zone->target_position = *target_position;
}

static sfVector2f random_target_position(entity_system_t *es, int i,
    c_position_t *entity_pos)
{
    sfVector2f target_position = {0};
    vec_t *component_zone = es->components[INTERACTION_ZONE];
    c_interaction_zone_t *tmp_zone = (c_interaction_zone_t *)
        ((void **)component_zone->data)[i];

    if (tmp_zone->count == tmp_zone->step_counter) {
        tmp_zone->step_counter = rand() % 10;
        tmp_zone->count = 0;
        init_random_direction(entity_pos, &target_position, tmp_zone);
    }
    if (tmp_zone->count < tmp_zone->step_counter)
        tmp_zone->count++;
    return tmp_zone->target_position;
}

void random_spell_move_system(entity_system_t *es, int entity)
{
    c_velocity_t *entity_vel = get_comp(es, VELOCITY, entity);
    c_position_t *entity_pos = get_comp(es, POSITION, entity);
    sfInt64 time_clock = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(entity_vel->clock)));
    sfVector2f target_pos = random_target_position(es, entity, entity_pos);
    float vector_x = target_pos.x - entity_pos->pos.x;
    float vector_y = target_pos.y - entity_pos->pos.y;
    float u_value = sqrtf(pow(vector_x, 2.0) + pow(vector_y, 2.0));

    if (u_value == 0 || (vector_x < 3.0 && vector_x > -3.0
    && vector_y > -3.0 && vector_y < 3.0))
        return;
    entity_vel->speed.x = vector_x / u_value *
        ((time_clock * entity_vel->velocity.x) / 100000);
    entity_vel->speed.y = vector_y / u_value *
        ((time_clock * entity_vel->velocity.y) / 100000);
}
