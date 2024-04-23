/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** key_pressed_component.h
*/

#pragma once

#include <SFML/Window/Keyboard.h>
#include "SFML/Window/Event.h"

typedef struct key_pressed_s {
    sfKeyEvent event;
    sfKeyCode code;
} c_key_pressed_t;
