/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_type.h
*/

#pragma once

#include "ecs.h"

typedef enum entity_e {
    PLAYER = 0,
    // NPC,
    // ENEMY,
    // BUTTON,
    // SKILL,
    // ITEM,
    // INVENTORY,
    LAST_ENTITY
} entity_t;

static const char *ENTITY_TYPE_CREATER[] = {
    "./config/entity/player_type.toml",
    // "./config/entity/npc_type.toml",
    // "./config/entity/enemy_type.toml"
};

#define ENTITY_TYPE_CREATER_PATH "./config/entity/"

#define TOTAL_TYPES (sizeof(ENTITY_TYPE_CREATER) / sizeof(char *))

int add_entities_type(entity_system_t *es, char const *filepath);
int search_for_config_files(const char *path, entity_system_t *es);
