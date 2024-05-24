/*
** EPITECH PROJECT, 2024
** RPG [WSL: Ubuntu]
** File description:
** key_mapping
*/

#pragma once

#include <stddef.h>


#include <SFML/Window/Export.h>
#include <SFML/Window/Keyboard.h>
#include "action.h"

#define KEYS_DEFINITION_PATH "./config/keys.toml"
#define ACTION_COUNT 5

typedef struct key_mapping_s {
    char *key_name;
    sfKeyCode key;
} key_mapping_t;

typedef struct key_callback_s {
    sfKeyCode key;
    int (*callback)(void *);
} key_callback_t;

typedef struct action_mapping_s {
    char *action_name;
    int (*callback)(void *);
} action_mapping_t;

typedef struct gamemode_keys_s {
    int mode;
    key_callback_t **key_map;
} gamemode_keys_t;

static const action_mapping_t ACTION_CONFIGS[ACTION_COUNT] = {
    {"ACTION-UP", &up_action},
    {"ACTION-DOWN", &down_action},
    {"ACTION-LEFT", &left_action},
    {"ACTION-RIGHT", &right_action},
    {"ACTION-ATTACK", &up_action}
};

static const key_mapping_t KEY_CONFIGS[] = {
    {"KEY-UP", sfKeyUp},
    {"KEY-DOWN", sfKeyDown},
    {"KEY-LEFT", sfKeyLeft},
    {"KEY-RIGHT", sfKeyRight},
    {"KEY-A", sfKeyA},
    {"KEY-B", sfKeyB},
    {"KEY-C", sfKeyC},
    {"KEY-D", sfKeyD},
    {"KEY-E", sfKeyE},
    {"KEY-F", sfKeyF},
    {"KEY-G", sfKeyG},
    {"KEY-H", sfKeyH},
    {"KEY-I", sfKeyI},
    {"KEY-J", sfKeyJ},
    {"KEY-K", sfKeyK},
    {"KEY-L", sfKeyL},
    {"KEY-M", sfKeyM},
    {"KEY-N", sfKeyN},
    {"KEY-O", sfKeyO},
    {"KEY-P", sfKeyP},
    {"KEY-Q", sfKeyQ},
    {"KEY-R", sfKeyR},
    {"KEY-S", sfKeyS},
    {"KEY-T", sfKeyT},
    {"KEY-U", sfKeyU},
    {"KEY-V", sfKeyV},
    {"KEY-W", sfKeyW},
    {"KEY-X", sfKeyX},
    {"KEY-Y", sfKeyY},
    {"KEY-Z", sfKeyZ},
    {"KEY-0", sfKeyNum0},
    {"KEY-1", sfKeyNum1},
    {"KEY-2", sfKeyNum2},
    {"KEY-3", sfKeyNum3},
    {"KEY-4", sfKeyNum4},
    {"KEY-5", sfKeyNum5},
    {"KEY-6", sfKeyNum6},
    {"KEY-7", sfKeyNum7},
    {"KEY-8", sfKeyNum8},
    {"KEY-9", sfKeyNum9},
    {"KEY-ESCAPE", sfKeyEscape},
    {"KEY-LCONTROL", sfKeyLControl},
    {"KEY-LSHIFT", sfKeyLShift},
    {"KEY-LALT", sfKeyLAlt},
    {"KEY-LSYSTEM", sfKeyLSystem},
    {"KEY-RCONTROL", sfKeyRControl},
    {"KEY-RSHIFT", sfKeyRShift},
    {"KEY-RALT", sfKeyRAlt},
    {"KEY-RSYSTEM", sfKeyRSystem},
    {"KEY-MENU", sfKeyMenu},
    {"KEY-LBRACKET", sfKeyLBracket}
};

static const int KEYS_COUNT = sizeof(KEY_CONFIGS) / sizeof(key_mapping_t);
