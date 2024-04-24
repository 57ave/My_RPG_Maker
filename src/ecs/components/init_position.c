/*
** EPITECH PROJECT, 2024
** init_position
** File description:
** init_position
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_position(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_position_t *new_component = calloc(sizeof(c_position_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    new_component->pos = *(sfVector2f *)pull_data(obj, "POSITION");
    new_component->new_pos = new_component->pos;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
