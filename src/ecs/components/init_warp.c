/*
** EPITECH PROJECT, 2024
** init_warp
** File description:
** init_warp
*/

#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static bool extract_sound(obj_t *obj, c_warp_t *new_component)
{
    char *tmp = NULL;

    tmp = (char *)pull_data(obj, "WARP-SOUND");
    if (tmp == NULL)
        return false;
    new_component->buffer = sfSoundBuffer_createFromFile(tmp);
    new_component->sound = sfSound_create();
    if (!new_component->buffer || !new_component->sound)
        return false;
    sfSound_setBuffer(new_component->sound, new_component->buffer);
    return true;
}

static bool extract_data(obj_t *obj, c_warp_t *new_component)
{
    int *tmp = NULL;

    tmp = (int *)pull_data(obj, "WARP-X");
    if (tmp == NULL) {
        return false;
    }
    new_component->warp.x = *tmp;
    tmp = (int *)pull_data(obj, "WARP-Y");
    if (tmp == NULL) {
        return false;
    }
    new_component->warp.y = *tmp;
    if (!extract_sound(obj, new_component))
        return false;
    return true;
}

int init_component_warp(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_warp_t *new_component = calloc(sizeof(c_warp_t), 1);

    if (!new_component)
        return EXIT_ERROR;
    if (!extract_data(obj, new_component)) {
        free(new_component);
        return EXIT_ERROR;
    }
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
