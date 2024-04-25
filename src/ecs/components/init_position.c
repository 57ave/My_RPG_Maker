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

static int extract_data(obj_t *obj, c_position_t *new_component)
{
    int *tmp = NULL;

    tmp = (int *)pull_data(obj, "POSITION-X");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    new_component->pos.x = *tmp;
    tmp = (int *)pull_data(obj, "POSITION-Y");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int init_component_position(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_position_t *new_component = calloc(sizeof(c_position_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    if (extract_data(obj, new_component) == EXIT_ERROR) {
        free(new_component);
        return EXIT_ERROR;
    }
    new_component->new_pos.x = new_component->pos.x;
    new_component->new_pos.y = new_component->pos.y;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
