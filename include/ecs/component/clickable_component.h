/*
** EPITECH PROJECT, 2024
** RPG [WSL: Ubuntu]
** File description:
** clickable_component
*/

#pragma once

#include <stdlib.h>

#define CLICK_CALLBACKS_COUNT 1

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

static const on_click_t CLICK_CALLBACKS[CLICK_CALLBACKS_COUNT] = {
    {"MENU-BUTTON", NULL}
};
