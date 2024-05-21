/*
** EPITECH PROJECT, 2024
** floor case init
** File description:
** init
*/

#ifndef FLOOR_CASE_INIT_H
    #define FLOOR_CASE_INIT_H

    #include "floor_case_struct.h"

typedef struct tailed_init_s {
    char *texture;
    char *sound;
    char character;
}tailed_init_t;

static const tailed_init_t FLOOR_INIT[] = {
    {"./assets/sprites/grass.png", "./assets/sounds/grass.wav", '#'},
    {"./assets/sprites/sand.png", "./assets/sounds/sand.wav", '+'},
    {"./assets/sprites/water.png", "./assets/sounds/water.wav", '~'},
};

static const size_t FLOOR_INIT_SIZE =
sizeof(FLOOR_INIT) / sizeof(tailed_init_t);

#endif
