/*
** EPITECH PROJECT, 2024
** init_warp
** File description:
** init_warp
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static int extract_data(obj_t *obj, c_warp_t *new_component)
{
    int *tmp = NULL;

    tmp = (int *)pull_data(obj, "WARP-X");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    new_component->warp.x = *tmp;
    tmp = (int *)pull_data(obj, "WARP-Y");
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    new_component->warp.y = *tmp;
    return EXIT_SUCCESS;
}

int init_component_warp(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_warp_t *new_component = calloc(sizeof(c_warp_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    if (extract_data(obj, new_component) == EXIT_ERROR) {
        free(new_component);
        return EXIT_ERROR;
    }
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
