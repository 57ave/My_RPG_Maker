/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** collision_component
*/

#pragma once

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>

typedef enum collision_type_e {
    CIRCLE = 0,
    RECTANGLE,
    LAST_COLLISION_TYPE
} collision_type_t;

typedef union collision_size_u {
    int radius;
    sfFloatRect rect;
} collision_size_t;

typedef union collision_shape_u {
    sfCircleShape *circle;
    sfRectangleShape *rectangle;
} collision_shape_t;

typedef struct collision_component {
    collision_type_t type;
    collision_shape_t shape;
    int wall;
    int offset_x;
    int offset_y;
} c_collision_t;
