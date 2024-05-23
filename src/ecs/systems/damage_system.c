/*
** EPITECH PROJECT, 2024
** damage_system
** File description:
** damage_system
*/

#include <stdbool.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static bool inflict_damage(c_damage_t *damage, c_health_t *health)
{
    int remaining_damage = 0;

    if (health->current_armor > 0) {
        health->current_armor -= damage->damage;
        if (health->current_armor >= 0)
            return true;
        if (health->current_armor < 0) {
            remaining_damage = health->current_armor * -1;
            health->current_armor = 0;
            health->current_health -= remaining_damage;
        }
    } else
        health->current_health -= damage->damage;
    if (health->current_health < 0)
        health->current_health = 0;
    return true;
}

static bool damage_type(c_damage_t *damage_1, c_health_t *health_2)
{
    if (damage_1 != NULL && health_2 != NULL)
        return inflict_damage(damage_1, health_2);
    return false;
}

static bool is_wall(entity_system_t *es, int entity1, int entity2)
{
    vec_t *component_collision = es->components[COLLISION];
    c_collision_t *collision_1 = (c_collision_t *)
        ((void **)component_collision->data)[entity1];
    c_collision_t *collision_2 = (c_collision_t *)
        ((void **)component_collision->data)[entity2];

    if (collision_1 == NULL || collision_2 == NULL)
        return true;
    if (collision_1->wall || collision_2->wall)
        return true;
    return false;
}

static bool invincibility_period(c_health_t *health_2)
{
    int time2 = sfClock_getElapsedTime(health_2->clock).microseconds / 1000000;

    if (time2 >= 1) {
        sfClock_restart(health_2->clock);
        return false;
    }
    return true;
}

void damage_entities(entity_system_t *es, int entity1, int entity2)
{
    vec_t *component_damage = es->components[DAMAGE];
    vec_t *component_health = es->components[HEALTH];
    c_damage_t *damage_1 = (c_damage_t *)
        ((void **)component_damage->data)[entity1];
    c_health_t *health_1 = (c_health_t *)
        ((void **)component_health->data)[entity1];
    c_health_t *health_2 = (c_health_t *)
        ((void **)component_health->data)[entity2];

    if ((damage_1 == NULL && health_1 == NULL) || health_2 == NULL)
        return;
    if (is_wall(es, entity1, entity2) || (health_1 != NULL &&
    (sfClock_getElapsedTime(health_1->clock).microseconds / 1000000 < 1) &&
    sfClock_getElapsedTime(health_2->clock).microseconds / 1000000 < 1))
        return;
    if (invincibility_period(health_2))
        return damage_entities(es, entity2, entity1);
    if (damage_type(damage_1, health_2))
        return;
    return damage_entities(es, entity2, entity1);
}
