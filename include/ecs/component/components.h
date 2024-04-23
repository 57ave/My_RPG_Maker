/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** component
*/

#pragma once

    #include <stddef.h>
    #include "position_component.h"
    #include "health_component.h"
    #include "velocity_component.h"
    #include "draw_component.h"
    #include "text_component.h"
    #include "key_pressed_component.h"
    #include "mouse_pressed.h"

typedef struct component_data_s {
    char *name;
    component_t index;
    size_t size;
    int (*init)();
} component_data_t;

typedef enum component_e {
    POSITION = 0,
    HEALTH,
    VELOCITY,
    DRAW,
    TEXT,
    KEY_PRESSED,
    MOUSE_PRESSED,
    LAST_COMPONENT
} component_t;

int init_component_position(void *es, obj_t *, component_t , int entity);

static const component_data_t const *COMPONENT_INIT_DATA = {
    {
        "POSITION", POSITION, &init_component_position, sizeof(_position_data)
    },
    {
        "HEALTH", HEALTH, &init_component_health, sizeof(_health_data)
    },
    {
        "VELOCITY", VELOCITY, &init_component_velocity, sizeof(_velocity_data)
    },
    {
        "DRAW", DRAW, &init_component_draw, sizeof(_draw_data)
    },
    {
        "TEXT", TEXT, &init_component_text, sizeof(_text_data)
    },
    {
        "KEY_PRESSED", KEY_PRESSED, &init_component_key_pressed,
        sizeof(_key_pressed)
    },
    {
        "MOUSE_PRESSED", MOUSE_PRESSED, &init_component_mouse_pressed,
        sizeof(_mouse_pressed)
    }
};
