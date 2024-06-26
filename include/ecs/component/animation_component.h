/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animation_component.h
*/

#pragma once

#include <SFML/System/Clock.h>

struct anim_data {
    sfIntRect rect;
    int x_add;
    int y_add;
    int current_frame;
    int nb_frame;
    int next_line_frame;
    int speed;
};

typedef enum direction {
    LEFT = 0,
    UP,
    RIGHT,
    DOWN,
    END_DIRECTION
} direction_t;

typedef struct animation_component {
    struct anim_data static_anim;
    direction_t direction;
    struct anim_data multidir_anim[END_DIRECTION];
    sfClock *clock;
} c_animation_t;
