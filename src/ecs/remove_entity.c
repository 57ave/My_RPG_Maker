/*
** EPITECH PROJECT, 2024
** remove_entity
** File description:
** remove_entity
*/

#include <stdbool.h>
#include <stdlib.h>
#include "ecs.h"
#include "position_component.h"
#include "components.h"
#include "macro.h"

int remove_entity(entity_system_t *es, int entity)
{
    for (int i = 0; i < es->total_indexes; ++i) {
        if (entity == es->all_indexes[i]) {
            es->all_indexes[i] = -1;
            break;
        }
    }
    return EXIT_SUCCESS;
}
