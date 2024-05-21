/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_component
*/

#include "vector.h"
#include "my_lib.h"
#include "macro.h"
#include "components.h"
#include "ecs.h"

int init_components(entity_system_t *es, void *component,
    component_t component_type, int entity)
{
    vec_t *vec = es->components[component_type];

    vec = push_index_vector(
            vec, component,
            COMPONENT_INIT_DATA[component_type].size, entity
    );
    if (vec == NULL) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
