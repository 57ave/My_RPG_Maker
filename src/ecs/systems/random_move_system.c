/*
** EPITECH PROJECT, 2024
** randaom_move_system
** File description:
** random_move_system
*/

/*
** EPITECH PROJECT, 2024
** aggro_system
** File description:
** aggro_system
*/

#include <SFML/System.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static sfVector2f random_target_position(entity_system_t *es, int i,
    c_position_t *entity_pos)
{
    sfVector2f target_position = {0};
    vec_t *component_zone = es->components[INTERACTION_ZONE];
    c_interaction_zone_t *tmp_zone = (c_interaction_zone_t *)
        ((void **)component_zone->data)[i];

    srand(time(NULL));
    if (rand() % 2 == 0)
        target_position.x = entity_pos->pos.x + rand() % 50;
    else
        target_position.x = entity_pos->pos.x - rand() % 50;
    if (rand() % 2 == 0)
        target_position.y = entity_pos->pos.y + rand() % 50;
    else
        target_position.y = entity_pos->pos.y - rand() % 50;
    tmp_zone->target_position = target_position;
    return target_position;
}

static void random_move_direction(entity_system_t *es, int i,
    c_velocity_t *entity_vel, c_position_t *entity_pos)
{
    sfInt64 time_clock = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(entity_vel->clock)));
    sfVector2f target_pos = random_target_position(es, i, entity_pos);
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

void random_move_entities(entity_system_t *es)
{
    entity_filter_t *filter = filter_entities(4, es, VELOCITY, POSITION,
        DAMAGE, INTERACTION_ZONE);
    vec_t *component_vel = es->components[VELOCITY];
    vec_t *component_pos = es->components[POSITION];
    c_velocity_t *tmp_vel = NULL;
    c_position_t *tmp_pos = NULL;

    for (int i = 0; i < filter->number; ++i) {
        tmp_vel = (c_velocity_t *)
            ((void **)component_vel->data)[filter->indexes[i]];
        tmp_pos = (c_position_t *)
        ((void **)component_pos->data)[filter->indexes[i]];
        if (!interaction_zone_entities(es, filter->indexes[i]) &&
        (rand() % 30) == 0) {
            random_move_direction(es, filter->indexes[i], tmp_vel, tmp_pos);
        }
    }
    free_filter(filter);
}
