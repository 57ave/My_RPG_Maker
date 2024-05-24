/*
** EPITECH PROJECT, 2024
** init_spell
** File description:
** init_spell
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_active_item(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_active_item_t *new_component = calloc(sizeof(c_active_item_t), 1);
    size_t *time = (size_t *)pull_data(obj, "ACTIVE_ITEM-TIME");

    if (!new_component || !time)
        return EXIT_ERROR;
    new_component->clock = sfClock_create();
    if (!new_component->clock)
        return EXIT_ERROR;
    new_component->time = *time;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
