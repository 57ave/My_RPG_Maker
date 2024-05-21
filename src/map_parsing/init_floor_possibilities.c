/*
** EPITECH PROJECT, 2024
** init floor possibilites
** File description:
** init
*/

#include <stdlib.h>
#include "floor/floor_case_init.h"

tailed_t **init_floor_possibilities(void)
{
    tailed_t **new = calloc(sizeof(tailed_t *), FLOOR_INIT_SIZE + 1);

    if (new == NULL)
        return NULL;
    for (int i = 0; i < FLOOR_INIT_SIZE; ++i) {
        new[i] = calloc(sizeof(tailed_t), 1);
        if (new[i] == NULL)
            return NULL;
        new[i]->character = FLOOR_INIT[i].character;
        new[i]->texture =
            sfTexture_createFromFile(FLOOR_INIT[i].texture, NULL);
        new[i]->buffer = sfSoundBuffer_createFromFile(FLOOR_INIT[i].sound);
        new[i]->sound = sfSound_create();
        if (!new[i]->buffer || !new[i]->sound)
            return NULL;
        sfSound_setBuffer(new[i]->sound, new[i]->buffer);
    }
    return new;
}