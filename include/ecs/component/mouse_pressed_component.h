/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** position_component.h
*/

#pragma once

#include <Vector2.h>
#include <SFML/Graphics/Sprite.h>
#include <stddef.h>

typedef struct position_s {
    sfVector2f prev_pos;
    sfVector2f new_pos;
} _position_data;
