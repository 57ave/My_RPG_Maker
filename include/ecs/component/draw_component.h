/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw_component.h
*/

#pragma once

#include <SFML/Graphics/Sprite.h>

typedef struct draw_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f size;
} c_draw_t;
