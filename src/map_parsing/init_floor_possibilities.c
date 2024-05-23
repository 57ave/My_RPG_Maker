/*
** EPITECH PROJECT, 2024
** init floor possibilites
** File description:
** init
*/

#include <stdlib.h>
#include <stdbool.h>
#include "floor/floor_case_struct.h"
#include "my_toml.h"
#include "macro.h"

static bool init_tail(tailed_t **new, obj_t *obj, size_t i)
{
    char *sprite = pull_data(obj, "SPRITE");
    char *sound = pull_data(obj, "SOUND");
    char *character = pull_data(obj, "CHAR");

    if (!sprite || !sound || !character)
        return false;
    new[i] = calloc(sizeof(tailed_t), 1);
    if (new[i] == NULL)
        return false;
    new[i]->character = character[0];
    new[i]->texture = sfTexture_createFromFile(sprite, NULL);
    new[i]->buffer = sfSoundBuffer_createFromFile(sound);
    new[i]->sound = sfSound_create();
    if (!new[i]->texture || !new[i]->buffer || !new[i]->sound)
        return NULL;
    sfSound_setBuffer(new[i]->sound, new[i]->buffer);
    new[i + 1] = NULL;
    return true;
}

tailed_t **init_floor_possibilities(void)
{
    tailed_t **new = NULL;
    char **content = read_file(MAP_CONFIG);
    obj_t **objs = NULL;
    int offset = 0;

    if (content == NULL)
        return NULL;
    objs = get_object(content, &offset, objs);
    if (objs == NULL)
        return NULL;
    for (size_t i = 0; objs[i] != NULL; ++i) {
        new = realloc(new, sizeof(tailed_t *) * (i + 2));
        if (new == NULL || !init_tail(new, objs[i], i)) {
            free_obj(objs);
            return NULL;
        }
    }
    free_obj(objs);
    return new;
}
