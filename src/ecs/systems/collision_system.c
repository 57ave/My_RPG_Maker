/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** collision_system
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdbool.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/CircleShape.h>
#include "collision_component.h"
#include "ecs.h"
#include "components.h"
#include "position_component.h"

static bool is_rect_colliding(c_position_t *pos_1, c_position_t *pos_2,
    c_collision_t *col)
{
    sfVector2f size = sfRectangleShape_getSize(col->shape.rectangle);
    sfFloatRect rect_1 = {pos_1->pos.x, pos_1->pos.y, size.x, size.y};
    sfFloatRect rect_2 = {pos_2->pos.x, pos_2->pos.y, size.x, size.y};

    if (sfFloatRect_intersects(&rect_1, &rect_2, NULL))
        return true;
    return false;
}

static bool is_circle_colliding(c_position_t *pos_1, c_position_t *pos_2,
    c_collision_t *col)
{
    int radius = sfCircleShape_getRadius(col->shape.circle);
    float distance = sqrtf(pow(pos_1->pos.x - pos_2->pos.x,
        2.0) + pow(pos_1->pos.y - pos_2->pos.y, 2.0));

    if (distance < radius)
        return true;
    return false;
}

static bool is_colliding(c_position_t *pos_1, c_position_t *pos_2,
    c_collision_t *col)
{
    switch (col->type) {
        case CIRCLE:
            return is_circle_colliding(pos_1, pos_2, col);
        default:
            return is_rect_colliding(pos_1, pos_2, col);
    }
}

bool collision_entities(entity_system_t *es, int index)
{
    vec_t *component_collision = (vec_t *)(es->components[COLLISION]);
    vec_t *component_pos = (vec_t *)(es->components[POSITION]);
    c_position_t *pos_1 = (c_position_t *)
        (((void **)(((vec_t *)
        (es->components[POSITION]))->data))[es->player]);
    c_position_t *pos_2 = (c_position_t *)
        ((void **)component_pos->data)[index];
    c_collision_t *collision = (c_collision_t *)
        ((void **)component_collision->data)[index];

    return is_colliding(pos_1, pos_2, collision);
}
