/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_collision
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/CircleShape.h>
#include <stdlib.h>
#include "collision_component.h"
#include "vector.h"
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "ecs.h"

static int set_collision_shape(c_collision_t *new_component, obj_t *obj)
{
    collision_size_t *collision_size =
        (collision_size_t *)pull_data(obj, "COLLISION-SIZE");

    switch (new_component->type) {
        case CIRCLE:
            new_component->shape.circle = sfCircleShape_create();
            if (!new_component->shape.circle)
                return EXIT_ERROR;
            sfCircleShape_setRadius(new_component->shape.circle,
                collision_size->radius);
            break;
        default:
            new_component->shape.rectangle = sfRectangleShape_create();
            if (!new_component->shape.rectangle)
                return EXIT_ERROR;
            sfRectangleShape_setSize(new_component->shape.rectangle,
                (sfVector2f){collision_size->rect.width,
                    collision_size->rect.height});
    }
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
    set_collision_shape(new_component, obj);
    if (init_components(es, (void *)new_component, type, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
