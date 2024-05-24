/*
** EPITECH PROJECT, 2024
** init_spell
** File description:
** init_spell
*/

#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static int find_callback(char *on_click)
{
    for (int i = 0; i < CLICK_CALLBACKS_COUNT; i++) {
        if (strcmp(on_click, CLICK_CALLBACKS[i].name) == 0)
            return i;
    }
    return -1;
}

int init_component_clickable(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_clickable_t *new_component = calloc(sizeof(c_clickable_t), 1);
    int *state = (int *)pull_data(obj, "CLICKABLE-STATE");
    char *on_click = pull_data(obj, "ON-CLICK");
    int index_clickable = -1;

    if (!new_component || !state || !on_click)
        return EXIT_ERROR;
    if (*state != IDLE && *state != HOVERED && *state != CLICKED)
        return EXIT_ERROR;
    index_clickable = find_callback(on_click);
    if (index_clickable == -1)
        return EXIT_ERROR;
    new_component->on_click = CLICK_CALLBACKS[index_clickable].callback;
    new_component->state = *state;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
