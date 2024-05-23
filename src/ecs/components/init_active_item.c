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
    char *file = (char *)pull_data(obj, "ACTIVE_ITEM-FILE");

    if (!new_component || !file)
        return EXIT_ERROR;
    new_component->file = read_file(file);
    if (!new_component->file)
        return EXIT_ERROR;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
