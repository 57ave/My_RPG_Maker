/*
** EPITECH PROJECT, 2024
** interaction_zone
** File description:
** init_interaction_zone
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_interaction_zone(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_interaction_zone_t *new_component =
        calloc(sizeof(c_interaction_zone_t), 1);
    int *radius = (int *)pull_data(obj, "INTERACTION_ZONE-RADIUS");

    if (!new_component || !radius)
        return EXIT_ERROR;
    new_component->radius = *radius;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
