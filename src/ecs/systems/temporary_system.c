/*
** EPITECH PROJECT, 2024
** temporary_system.c
** File description:
** temporary_system
*/

#include <stdbool.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

bool temporary_system(entity_system_t *es, int entity)
{
    vec_t *component_temp = es->components[TEMPORARY];
    c_temporary_t *temporary = (c_temporary_t *)
        ((void **)component_temp->data)[entity];

    if (!temporary)
        return false;
    if ((sfClock_getElapsedTime(temporary->clock).microseconds / 1000000) >
    (int)temporary->time)
        return true;
    return false;
}
