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
#include "floor/floor_struct.h"
#include "systems.h"

static int get_floor_y_size(floor_t ***floor)
{
    int i = 0;

    while (floor[i])
        ++i;
    return i;
}

static int get_floor_x_size(floor_t **floor)
{
    int i = 0;

    while (floor[i])
        ++i;
    return i;
}

static void play_sound(floor_t ***floor, c_position_t *pos,
    c_velocity_t *vel)
{
    int index_y = 0;
    int index_x = 0;

    if ((vel->speed.x != 0 || vel->speed.y != 0) &&
        sfClock_getElapsedTime(vel->floor_sound).microseconds > 400000) {
        sfClock_restart(vel->floor_sound);
        index_y = (int)((pos->pos.y) / (TAILED_SIZE)) + 2;
        index_x = (int)(pos->pos.x / (TAILED_SIZE));
        if (index_y < get_floor_y_size(floor) &&
            index_x < get_floor_x_size(floor[index_y]) &&
            floor[index_y][index_x]->sound != NULL) {
            sfSound_play(floor[index_y][index_x]->sound);
        }
    }
}

static void reset_speed_entities(c_velocity_t *velocity_entity)
{
    velocity_entity->speed.x = 0;
    velocity_entity->speed.y = 0;
    sfClock_restart(velocity_entity->clock);
}

static bool check_collisions(entity_filter_t *collisions,
    int entity, entity_system_t *es)
{
    vec_t *component_col = (vec_t *)(es->components[COLLISION]);

    for (int i = 0; i < collisions->number; ++i) {
        if (collisions->indexes[i] == entity)
            continue;
        if (collision_entities(es, entity, collisions->indexes[i]))
            damage_entities(es, entity, collisions->indexes[i]);
        if (((c_collision_t *)
            ((void **)component_col->data)[collisions->indexes[i]])->wall &&
            collision_entities(es, entity, collisions->indexes[i])) {
            return true;
        }
    }
    return false;
}

void move_entities(entity_system_t *es, floor_t ***floor)
{
    entity_filter_t *filter = filter_entities(2, es, VELOCITY, POSITION);
    entity_filter_t *collision_filter = filter_entities(1, es, COLLISION);
    c_position_t *tmp_pos = NULL;
    c_velocity_t *tmp_vel = NULL;

    for (int i = 0; i < filter->number; ++i) {
        tmp_pos = (c_position_t *)get_comp(es, POSITION, filter->indexes[i]);
        tmp_vel = (c_velocity_t *)get_comp(es, VELOCITY, filter->indexes[i]);
        tmp_pos->pos.x += tmp_vel->speed.x;
        tmp_pos->pos.y += tmp_vel->speed.y;
        if (check_collisions(collision_filter, filter->indexes[i], es)) {
            tmp_pos->pos.x -= tmp_vel->speed.x;
            tmp_pos->pos.y -= tmp_vel->speed.y;
        }
        play_sound(floor, tmp_pos, tmp_vel);
        reset_speed_entities(tmp_vel);
    }
    free_filter(filter);
}
