/*
** EPITECH PROJECT, 2024
** init_health
** File description:
** init_health
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_health(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_health_t *new_component = calloc(sizeof(c_health_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    new_component->current_health = *(int *)pull_data(obj, "HEALTH_CURRENT");
    new_component->max_health = new_component->current_health;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
