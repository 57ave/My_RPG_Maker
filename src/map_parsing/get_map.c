/*
** EPITECH PROJECT, 2024
** get map
** File description:
** function to get the map
*/

#include <SFML/Graphics.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "functions.h"
#include "my_lib.h"
#include "floor/floor_struct.h"
#include "floor/floor_case_struct.h"

static floor_t *init_floor_case(tailed_t *possibility)
{
    floor_t *new = calloc(sizeof(floor_t), 1);

    if (new == NULL)
        return NULL;
    if (!possibility)
        return new;
    new->sprite = sfSprite_create();
    if (new->sprite == NULL)
        return NULL;
    sfSprite_setTexture(new->sprite, possibility->texture, true);
    sfSprite_setScale(new->sprite, sprite_size(possibility->texture,
        (sfVector2f){TAILED_SIZE, TAILED_SIZE}));
    sfSprite_setOrigin(new->sprite,
        (sfVector2f){0.0, sfTexture_getSize(possibility->texture).y});
    new->sound = possibility->sound;
    return new;
}

static bool fill_sprite(char character, floor_t **sprite,
    tailed_t **possibilities)
{
    for (size_t j = 0; possibilities[j]; ++j) {
        if (possibilities[j]->character == character)
            *sprite = init_floor_case(possibilities[j]);
        else
            continue;
        if (*sprite == NULL)
            return false;
        return true;
    }
    *sprite = init_floor_case(NULL);
    return !(*sprite == NULL);
}

static bool fill_sprite_line(char const *const char_line,
    floor_t **sprite_line, tailed_t **possibilities)
{
    size_t i = 0;

    while (char_line[i] != '\0') {
        if (!fill_sprite(char_line[i], &sprite_line[i], possibilities)) {
            return false;
        }
        ++i;
    }
    return true;
}

static void set_line(floor_t ***sprites, int i)
{
    for (size_t j = 0; sprites[i][j]; ++j) {
        if (sprites[i][j]->sprite == NULL)
            continue;
        sfSprite_setPosition(sprites[i][j]->sprite,
        (sfVector2f){(TAILED_SIZE) * j, (TAILED_SIZE) * i});
    }
}

static floor_t ***get_sprite_map(char const *const *const char_map,
    tailed_t **possibilities)
{
    floor_t ***sprites = calloc(sizeof(floor_t **),
        my_arraylen(char_map) + 1);

    for (size_t j = 0; char_map[j]; ++j) {
        sprites[j] = calloc(sizeof(floor_t *), strlen(char_map[j]) + 1);
        if (sprites[j] == NULL)
            return NULL;
        if (!fill_sprite_line(char_map[j], sprites[j], possibilities))
            return NULL;
    }
    for (size_t i = 0; sprites[i]; ++i)
        set_line(sprites, i);
    return sprites;
}

floor_t ***get_map(tailed_t **possibilities, char const *const path)
{
    char **char_map = get_char_map(path);

    if (char_map == NULL)
        return NULL;
    return get_sprite_map((char const *const *const)char_map, possibilities);
}
