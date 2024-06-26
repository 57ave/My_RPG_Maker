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

static int extract_data(obj_t *obj, c_velocity_t *new_component)
{
    int *tmp = NULL;

    tmp = (int *)pull_data(obj, "VELOCITY-X");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    new_component->velocity.x = *tmp;
    tmp = (int *)pull_data(obj, "VELOCITY-Y");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    new_component->velocity.y = *tmp;
    return EXIT_SUCCESS;
}

int init_component_velocity(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_velocity_t *new_component = calloc(sizeof(c_velocity_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    if (extract_data(obj, new_component) == EXIT_ERROR) {
        free(new_component);
        return EXIT_ERROR;
    }
    new_component->speed.x = 0;
    new_component->speed.y = 0;
    new_component->clock = sfClock_create();
    new_component->floor_sound = sfClock_create();
    if (!new_component->clock || !new_component->floor_sound) {
        free(new_component);
        return EXIT_ERROR;
    }
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
