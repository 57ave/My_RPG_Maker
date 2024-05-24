/*
** EPITECH PROJECT, 2024
** spell_system
** File description:
** spell_system
*/

#include <stdlib.h>
#include <math.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"
#include "macro.h"

static bool check_spell_collisions(entity_system_t *es, int entity)
{
    entity_filter_t *filter_collision = filter_entities(1, es, COLLISION);

    for (int i = 0; i < filter_collision->number; ++i) {
        if (filter_collision->indexes[i] != entity &&
        collision_entities(es, entity, filter_collision->indexes[i])) {
            damage_entities(es, entity, filter_collision->indexes[i]);
            free_filter(filter_collision);
            return true;
        }
    }
    free_filter(filter_collision);
    return false;
}

static void move_spell_entities(entity_system_t *es, int entity,
    int target_entity)
{
    if (target_entity != -1 &&
    interaction_zone_entities(es, target_entity, entity))
        aggro_spell_system(es, entity, target_entity);
    else
        random_spell_move_system(es, entity);
}

static bool targ_condition(entity_system_t *es, int i,
    int *near_entities)
{
    c_health_t *tmp_health = get_comp(es, HEALTH, near_entities[i]);
    c_game_mode_t *tmp_mode = get_comp(es, GAME_MODE, near_entities[i]);

    if (tmp_health != NULL && tmp_mode != NULL && tmp_mode == 0 &&
    es->player != near_entities[i])
        return true;
    return false;
}

static int search_best_target(entity_system_t *es, int entity,
    int *near_entities, int count)
{
    int target = -1;
    int distance = 0;
    int tmp_distance = 0;
    c_position_t *entity_pos = get_comp(es, POSITION, entity);
    c_position_t *tmp_pos = NULL;

    for (int i = 0; i < count; ++i) {
        tmp_pos = get_comp(es, POSITION, near_entities[i]);
        tmp_distance = sqrt(pow(tmp_pos->pos.x - entity_pos->pos.x, 2) +
            pow(tmp_pos->pos.y - entity_pos->pos.y, 2));
        if (i == 0)
            distance = tmp_distance;
        if (targ_condition(es, i, near_entities) && tmp_distance <= distance){
            distance = tmp_distance;
            target = near_entities[i];
        }
    }
    return target;
}

static int get_target_entity(entity_system_t *es, int entity)
{
    int count = 0;
    int *near_entities = get_near_entities(es, entity, &count);
    int target = 0;

    if (near_entities == NULL)
        return -1;
    target = search_best_target(es, entity, near_entities, count);
    free(near_entities);
    return target;
}

void spell_entities(entity_system_t *es)
{
    entity_filter_t *filter = filter_entities(5, es, TEMPORARY, DAMAGE,
    COLLISION, POSITION, VELOCITY);
    int target_entity = -1;
    int error = EXIT_SUCCESS;

    for (int i = 0; i < filter->number; ++i) {
        target_entity = get_target_entity(es, filter->indexes[i]);
        if (check_spell_collisions(es, filter->indexes[i]) ||
        temporary_system(es, filter->indexes[i]))
            error = remove_entity(es, filter->indexes[i]);
        if (error == EXIT_ERROR)
            return;
        move_spell_entities(es, filter->indexes[i], target_entity);
    }
    free_filter(filter);
}
