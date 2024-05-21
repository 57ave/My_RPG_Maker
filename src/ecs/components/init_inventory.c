/*
** EPITECH PROJECT, 2024
** init_inventory
** File description:
** init_inventory
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_inventory(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_inventory_t *new_component = calloc(sizeof(c_inventory_t), 1);
    int *size = (int *)pull_data(obj, "INVENTORY-SIZE");

    if (!new_component || !size)
        return EXIT_ERROR;
    new_component->size = *size;
    new_component->object_tab = calloc(sizeof(int), new_component->size);
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
