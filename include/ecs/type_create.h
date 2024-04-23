/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_type.h
*/

#pragma once

typedef enum entity_e {
    PLAYER = 0,
    NPC,
    ENEMY,
    BUTTON,
    SKILL,
    ITEM,
    INVENTORY,
    LAST_ENTITY
} entity_t;

static const char *entity_type_creater[] = {
    "./config/entity/player_type.toml",
    "./config/entity/npc_type.toml",
    "./config/entity/enemy_type.toml"
};

    #define TOTAL_TYPES (sizeof(entity_type_creater) / sizeof(char *))
