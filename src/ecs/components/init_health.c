/*
** EPITECH PROJECT, 2024
** init_health
** File description:
** init_health
*/

#include <stdlib.h>
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static int init_life_bar(c_health_t *health, obj_t *obj)
{
    int *size_x = (int *)pull_data(obj, "HEALTH-BAR_SIZE_X");
    int *size_y = (int *)pull_data(obj, "HEALTH-BAR_SIZE_Y");

    if (!size_x || !size_y || *size_x == 0 || *size_y == 0)
        return EXIT_ERROR;
    health->life_bar_size.x = *size_x;
    health->life_bar_size.y = *size_y;
    health->health_rect = sfRectangleShape_create();
    health->armor_rect = sfRectangleShape_create();
    if (!health->health_rect || !health->armor_rect)
        return EXIT_ERROR;
    sfRectangleShape_setFillColor(health->health_rect, sfGreen);
    sfRectangleShape_setFillColor(health->armor_rect, sfBlue);
    sfRectangleShape_setSize(health->health_rect, health->life_bar_size);
    sfRectangleShape_setSize(health->armor_rect, health->life_bar_size);
    return EXIT_SUCCESS;
}

int init_component_health(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_health_t *new_component = calloc(sizeof(c_health_t), 1);
    int *health = (int *)pull_data(obj, "HEALTH-LIFE");
    int *armor = (int *)pull_data(obj, "HEALTH-ARMOR");

    if (!new_component || !health || *health <= 0)
        return EXIT_ERROR;
    new_component->current_health = *health;
    new_component->max_health = new_component->current_health;
    if (!armor)
        new_component->current_armor = 0;
    else
        new_component->current_armor = *armor;
    new_component->max_armor = new_component->current_armor;
    new_component->clock = sfClock_create();
    if (!new_component->clock ||
    init_life_bar(new_component, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
