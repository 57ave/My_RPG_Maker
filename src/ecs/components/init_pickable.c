/*
** EPITECH PROJECT, 2024
** init_hpickable
** File description:
** init_pickable
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_pickable(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_pickable_t *new_component = calloc(sizeof(c_pickable_t), 1);
    bool *is_pickable = (bool *)pull_data(obj, "PICKABLE-BOOL");

    if (!new_component || !is_pickable)
        return EXIT_ERROR;
    new_component->pickable = *is_pickable;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
