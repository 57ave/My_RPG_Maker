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

#define ENTITY_DIRECTORY_PATH "./config/entity/"

#define TOTAL_TYPES (sizeof(ENTITY_TYPE_CREATER) / sizeof(char *))

int add_entities_from_path(entity_system_t *es, char const *filepath);
int search_for_config_files(const char *path, entity_system_t *es);
