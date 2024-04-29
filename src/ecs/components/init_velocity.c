/*
** EPITECH PROJECT, 2024
** init_velocity
** File description:
** init_velocity
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_velocity(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_velocity_t *new_component = calloc(sizeof(c_velocity_t), 1);
    sfVector2f *velocity = (sfVector2f *)pull_data(obj, "VELOCITY-VELOCITY");

    if (!new_component || !velocity)
        return EXIT_ERROR;
    new_component->velocity = *velocity;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
