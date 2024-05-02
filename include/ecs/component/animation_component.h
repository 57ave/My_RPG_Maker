/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animation_component.h
*/

#pragma once

typedef struct animation_component {
    sfIntRect initial_rect;
    sfIntRect current_rect;
    int x_add;
    int y_add;
    int nb_frame;
    int next_line_frame;
} c_animation_t;
