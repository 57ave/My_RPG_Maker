/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_collision
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Types.h>
#include <stdlib.h>
#include "collision_component.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static int create_circle_collision(c_collision_t *new_component, obj_t *obj)
{
    int *radius = (int *)pull_data(obj, "COLLISION-RADIUS");

    new_component->shape.circle = sfCircleShape_create();
    if (!new_component->shape.circle || !radius)
        return EXIT_ERROR;
    sfCircleShape_setRadius(new_component->shape.circle, *radius);
    return EXIT_SUCCESS;
}

static int create_rect_collision(c_collision_t *new_component, obj_t *obj)
{
    int *width = (int *)pull_data(obj, "COLLISION-WIDTH");
    int *height = (int *)pull_data(obj, "COLLISION-HEIGHT");

    new_component->shape.rectangle = sfRectangleShape_create();
    if (!new_component->shape.rectangle || !width || !height)
        return EXIT_ERROR;
    sfRectangleShape_setSize(new_component->shape.rectangle,
        (sfVector2f){(float)*width, (float)*height});
    return EXIT_SUCCESS;
}

static int set_collision_shape(c_collision_t *new_component, obj_t *obj)
{
    switch (new_component->type) {
        case CIRCLE:
            return create_circle_collision(new_component, obj);
        default:
            return create_rect_collision(new_component, obj);
    }
    return EXIT_SUCCESS;
}

static int set_other_infos(c_collision_t *new_component, obj_t *obj)
{
    int *offset_x = (int *)pull_data(obj, "COLLISION-OFFSET_X");
    int *offset_y = (int *)pull_data(obj, "COLLISION-OFFSET_Y");
    int *wall = (int *)pull_data(obj, "COLLISION-WALL");

    if (!offset_x || !offset_y || !wall)
        return EXIT_ERROR;
    new_component->offset_x = *offset_x;
    new_component->offset_y = *offset_y;
    new_component->wall = *wall;
    return EXIT_SUCCESS;
}

int init_component_collision(entity_system_t *es, obj_t *obj,
    component_t type, int entity)
{
    c_collision_t *new_component = calloc(sizeof(c_collision_t), 1);
    collision_type_t *collision_type =
        (collision_type_t *)pull_data(obj, "COLLISION-TYPE");

    if (!new_component || !collision_type)
        return EXIT_ERROR;
    new_component->type = *collision_type;
    if (set_collision_shape(new_component, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    if (set_other_infos(new_component, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
