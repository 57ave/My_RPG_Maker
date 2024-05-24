/*
** EPITECH PROJECT, 2024
** RPG [WSL: Ubuntu]
** File description:
** clickable_component
*/

#pragma once

#include <stdlib.h>

typedef enum clickable_state_e {
    IDLE = 0,
    HOVERED = 1,
    CLICKED = 2
} c_clickable_state_t;

typedef struct clickable_component_s {
    c_clickable_state_t state;
    void (*on_click)();
} c_clickable_t;

typedef struct on_click_s {
    char *name;
    void (*callback)();
} on_click_t;

void play(void *es);

static const on_click_t CLICK_CALLBACKS[] = {
    {"PLAY-BUTTON", play},
};

static const int CLICK_CALLBACKS_COUNT =
sizeof(CLICK_CALLBACKS) / sizeof(on_click_t);
