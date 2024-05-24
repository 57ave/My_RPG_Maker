/*
** EPITECH PROJECT, 2024
** RPG [WSL: Ubuntu]
** File description:
** read_keys
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ecs.h"
#include "key_mapping.h"
#include "my_toml.h"

static void print_gamemode_keys(entity_system_t *es)
{
    for (int i = 0; i < GAMEMODE_COUNT; ++i) {
        if (es->keys[i].key_map == NULL)
            continue;
        printf("Gamemode: %d\n", es->keys[i].mode);
        for (int j = 0; j < ACTION_COUNT; ++j) {
            printf("Key: %d | Callback: %p\n", es->keys[i].key_map[j]->key,
                es->keys[i].key_map[j]->callback);
        }
    }
}

static void define_key(char *action_name, key_callback_t **key_map,
    int i, int j)
{
    key_callback_t *key_callback = NULL;

    if (key_map[j])
    if (strcmp(action_name, ACTION_CONFIGS[j].action_name) == 0) {
        key_callback = calloc(sizeof(key_callback_t), 1);
        key_callback->key = KEY_CONFIGS[i].key;
        key_callback->callback = ACTION_CONFIGS[j].callback;
        key_map[j] = key_callback;
    }
}

static int init_keys_gamemode(entity_system_t *es, obj_t *obj, int mode)
{
    key_callback_t **key_map =
    calloc(sizeof(key_callback_t *), ACTION_COUNT + 1);
    char *action_name = NULL;

    if (key_map == NULL)
        return EXIT_FAILURE;
    for (int i = 0; i < KEYS_COUNT; ++i) {
        action_name = pull_data(obj, KEY_CONFIGS[i].key_name);
        if (action_name == NULL)
            continue;
        for (int j = 0; j < ACTION_COUNT; ++j) {
            define_key(action_name, key_map, i, j);
        }
    }
    es->keys[mode].mode = mode;
    es->keys[mode].key_map = key_map;
    return EXIT_SUCCESS;
}

static int add_keys_from_path(entity_system_t *es, char const *filepath)
{
    char **content = read_file(filepath);
    obj_t **obj_tab = NULL;
    int offset = 0;

    obj_tab = get_object(content, &offset, obj_tab);
    if (obj_tab == NULL)
        return EXIT_FAILURE;
    for (int mode = 0; obj_tab[mode] != NULL; ++mode) {
        if (init_keys_gamemode(es, obj_tab[mode], mode) == EXIT_FAILURE) {
            free_obj(obj_tab);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int read_keys_from_file(entity_system_t *es, const char *filepath)
{
    if (add_keys_from_path(es, filepath) == EXIT_FAILURE)
        return EXIT_FAILURE;
    print_gamemode_keys(es);
    return EXIT_SUCCESS;
}
