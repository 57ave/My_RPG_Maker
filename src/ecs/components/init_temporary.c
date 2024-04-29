/*
** EPITECH PROJECT, 2024
** init_temporary
** File description:
** init_temporary
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_temporary(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_temporary_t *new_component = calloc(sizeof(c_temporary_t), 1);
    size_t *time = (size_t *)pull_data(obj, "TEMPORARY-TIME");

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
