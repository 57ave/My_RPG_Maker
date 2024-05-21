/*
** EPITECH PROJECT, 2024
** warp compoent
** File description:
** warp
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

typedef struct warp_s {
    sfVector2f warp;
    sfSoundBuffer *buffer;
    sfSound *sound;
} c_warp_t;
