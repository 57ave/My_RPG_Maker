/*
** EPITECH PROJECT, 2024
** get_component
** File description:
** get the comp
*/

#include "ecs.h"
#include "components.h"

void *get_comp(entity_system_t *es, component_t component, int entity)
{
    if (entity == -1)
        return NULL;
    return (((void **)((vec_t *)es->components[component])->data)[entity]);
}
