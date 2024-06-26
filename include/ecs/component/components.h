/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** component
*/

#pragma once

    #include <stddef.h>
    #include <stdbool.h>
    #include "my_toml.h"
    #include "position_component.h"
    #include "health_component.h"
    #include "velocity_component.h"
    #include "draw_component.h"
    #include "text_component.h"
    #include "key_pressed_component.h"
    #include "mouse_pressed_component.h"
    #include "game_mode_component.h"
    #include "temporary_component.h"
    #include "damage_component.h"
    #include "animation_component.h"
    #include "interaction_zone_component.h"
    #include "collision_component.h"
    #include "inventory_component.h"
    #include "warp_component.h"
    #include "pickable_component.h"
    #include "active_item_component.h"
    #include "clickable_component.h"
    #include "ecs.h"

entity_system_t *init_entity_system(entity_system_t *es);
typedef enum component_e {
    POSITION = 0,
    DAMAGE,
    VELOCITY,
    DRAW,
    TEXT,
    // KEY_PRESSED,
    // MOUSE_PRESSED,
    GAME_MODE,
    TEMPORARY,
    HEALTH,
    ANIMATION,
    INTERACTION_ZONE,
    COLLISION,
    WARP,
    INVENTORY,
    PICKABLE,
    ACTIVE_ITEM,
    CLICKABLE,
    LAST_COMPONENT
} component_t;

void *get_comp(entity_system_t *es, component_t component, int entity);
int init_components(entity_system_t *es, void *component,
    component_t component_type, int entity);
bool get_entities(entity_system_t *es);
int *get_near_entities(entity_system_t *es, int entity, int *count);

typedef struct component_data_s {
    char *name;
    component_t index;
    int (*init)();
    size_t size;
} component_data_t;

int init_components(entity_system_t *es, void *component,
    component_t component_type, int entity);

int init_component_position(entity_system_t *es,
    obj_t *, component_t, int entity);
int init_component_velocity(entity_system_t *es,
    obj_t *, component_t, int entity);
int init_component_health(entity_system_t *es,
    obj_t *, component_t, int entity);
int init_component_draw(entity_system_t *es,
    obj_t *, component_t, int entity);
int init_component_text(entity_system_t *es,
    obj_t *, component_t, int entity);
// int init_component_key_pressed(entity_system_t *es,
//     obj_t *, component_t, int entity);
// int init_component_mouse_pressed(entity_system_t *es, obj_t *,
//     component_t, int entity);
int init_component_game_mode(entity_system_t *es, obj_t *,
    component_t, int entity);
int init_component_temporary(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_damage(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_animation(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_interaction_zone(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_collision(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_warp(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_inventory(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_pickable(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_active_item(entity_system_t *es,
    obj_t *obj, component_t type, int entity);
int init_component_clickable(entity_system_t *es,
    obj_t *obj, component_t type, int entity);

static const component_data_t COMPONENT_INIT_DATA[] = {
    {
        "POSITION", POSITION, &init_component_position, sizeof(c_position_t *)
    },
    {
        "DAMAGE", DAMAGE, &init_component_damage,
        sizeof(c_damage_t *)
    },
    {
        "VELOCITY", VELOCITY, &init_component_velocity, sizeof(c_velocity_t *)
    },
    {
        "DRAW", DRAW, &init_component_draw, sizeof(c_draw_t *)
    },
    {
        "TEXT", TEXT, &init_component_text, sizeof(c_text_t *)
    },
    // {
    //     "KEY_PRESSED", KEY_PRESSED, &init_component_key_pressed,
    //     sizeof(c_key_pressed_t *)
    // },
    // {
    //     "MOUSE_PRESSED", MOUSE_PRESSED, &init_component_mouse_pressed,
    //     sizeof(c_mouse_pressed_t *)
    // },
    {
        "GAME_MODE", GAME_MODE, &init_component_game_mode,
        sizeof(c_game_mode_t *)
    },
    {
        "TEMPORARY", TEMPORARY, &init_component_temporary,
        sizeof(c_temporary_t *)
    },
    {
        "HEALTH", HEALTH, &init_component_health, sizeof(c_health_t *)
    },
    {
        "ANIMATION", ANIMATION, &init_component_animation,
        sizeof(c_animation_t *)
    },
    {
        "INTERACTION_ZONE", INTERACTION_ZONE, &init_component_interaction_zone,
        sizeof(c_interaction_zone_t *)
    },
    {
        "COLLISION", COLLISION, &init_component_collision,
        sizeof(c_collision_t *)
    },
    {
        "WARP", WARP, &init_component_warp, sizeof(c_warp_t *)
    },
    {
        "INVENTORY", INVENTORY, &init_component_inventory,
        sizeof(c_inventory_t *)
    },
    {
        "PICKABLE", PICKABLE, &init_component_pickable,
        sizeof(c_pickable_t *)
    },
    {
        "ACTIVE_ITEM", ACTIVE_ITEM, &init_component_active_item,
        sizeof(c_active_item_t *)
    },
    {
        "CLICKABLE", CLICKABLE, &init_component_clickable,
        sizeof(c_clickable_t *)
    }
};

static const size_t NB_OF_COMPONENT =
sizeof(COMPONENT_INIT_DATA) / sizeof(component_data_t);
