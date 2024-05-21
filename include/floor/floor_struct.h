/*
** EPITECH PROJECT, 2024
** floor struct
** File description:
** struct for floor
*/

#ifndef FLOOR_STRUCT_H
    #define FLOOR_STRUCT_H

    #include <stdbool.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

static const double TAILED_SIZE = 50.0;

typedef struct floor_s {
    sfSprite *sprite;
    sfSound *sound;
    sfVector2i size;
}floor_t;

#endif
