/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** collision_system
*/

#include <stdbool.h>
#include <stddef.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/CircleShape.h>
#include "collision_component.h"
#include "ecs.h"
#include "components.h"

static bool is_rect_colliding(c_collision_t *col_1, c_collision_t *col_2)
{
    sfFloatRect rect_1 =
        sfRectangleShape_getGlobalBounds(col_1->shape.rectangle);
    sfFloatRect rect_2 =
        sfRectangleShape_getGlobalBounds(col_2->shape.rectangle);

    return sfFloatRect_intersects(&rect_1, &rect_2, NULL);
}

static bool is_circle_colliding(c_collision_t *col_1, c_collision_t *col_2)
{
    sfFloatRect rect_1 =
        sfCircleShape_getGlobalBounds(col_1->shape.circle);
    sfFloatRect rect_2 =
        sfCircleShape_getGlobalBounds(col_2->shape.circle);

    return sfFloatRect_intersects(&rect_1, &rect_2, NULL);
}

static bool is_circle_rect_colliding(c_collision_t *col_1,
    c_collision_t *col_2)
{
    sfFloatRect rect_1 = {0};
    sfFloatRect rect_2 = {0};

    if (col_1->type == CIRCLE) {
        rect_1 = sfCircleShape_getGlobalBounds(col_1->shape.circle);
        rect_2 = sfRectangleShape_getGlobalBounds(col_2->shape.rectangle);
    } else {
        rect_1 = sfRectangleShape_getGlobalBounds(col_1->shape.rectangle);
        rect_2 = sfCircleShape_getGlobalBounds(col_2->shape.circle);
    }
    return sfFloatRect_intersects(&rect_1, &rect_2, NULL);
}

bool collision_entities(entity_system_t *es, int e_1, int e_2)
{
    vec_t *component_collision = (vec_t *)(es->components[COLLISION]);
    c_collision_t *col_1 = (c_collision_t *)
        ((void **)component_collision->data)[e_1];
    c_collision_t *col_2 = (c_collision_t *)
        ((void **)component_collision->data)[e_2];

    if (col_1 == NULL || col_2 == NULL)
        return false;
    if (col_1->type == RECTANGLE && col_2->type == RECTANGLE)
        return is_rect_colliding(col_1, col_2);
    if (col_1->type == CIRCLE && col_2->type == CIRCLE)
        return is_circle_colliding(col_1, col_2);
    return is_circle_rect_colliding(col_1, col_2);
}
