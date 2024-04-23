/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** key_pressed_component.h
*/

#pragma once

#include <Event.h>
#include <SFML/Window/Export.h>

typedef struct key_pressed_s {
    sfKeyEvent event;
    sfKeyCode code;
} _position_data;
