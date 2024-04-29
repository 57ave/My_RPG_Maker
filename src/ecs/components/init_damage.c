/*
** EPITECH PROJECT, 2024
** init_damage
** File description:
** init_damage
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

int init_component_damage(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_damage_t *new_component = calloc(sizeof(c_damage_t), 1);
    int *damage = (int *)pull_data(obj, "DAMAGE-DAMAGE");

    if (!new_component || !damage)
        return EXIT_ERROR;
    new_component->damage = *damage;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
