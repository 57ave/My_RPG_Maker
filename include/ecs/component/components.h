/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** component
*/

#pragma once

    #include <stddef.h>
    #include "my_toml.h"
    #include "type_create.h"
    #include "position_component.h"
    #include "health_component.h"
    #include "velocity_component.h"
    #include "draw_component.h"
    #include "text_component.h"
    #include "key_pressed_component.h"
    #include "mouse_pressed_component.h"

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

typedef struct component_data_s {
    char *name;
    component_t index;
    int (*init)();
    size_t size;
} component_data_t;

int init_component_position(void *es, obj_t *, component_t, int entity);
int init_component_velocity(void *es, obj_t *, component_t, int entity);
int init_component_health(void *es, obj_t *, component_t, int entity);
int init_component_draw(void *es, obj_t *, component_t, int entity);
int init_component_text(void *es, obj_t *, component_t, int entity);
int init_component_key_pressed(void *es, obj_t *, component_t, int entity);
int init_component_mouse_pressed(void *es, obj_t *, component_t, int entity);

static const component_data_t COMPONENT_INIT_DATA[] = {
    {
        "POSITION", POSITION, &init_component_position, sizeof(position_c)
    },
    {
        "HEALTH", HEALTH, &init_component_health, sizeof(health_c)
    },
    {
        "VELOCITY", VELOCITY, &init_component_velocity, sizeof(velocity_c)
    },
    {
        "DRAW", DRAW, &init_component_draw, sizeof(draw_c)
    },
    {
        "TEXT", TEXT, &init_component_text, sizeof(text_c)
    },
    {
        "KEY_PRESSED", KEY_PRESSED, &init_component_key_pressed,
        sizeof(key_pressed_c)
    },
    {
        "MOUSE_PRESSED", MOUSE_PRESSED, &init_component_mouse_pressed,
        sizeof(mouse_pressed_c)
    }
};
