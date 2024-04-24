/*
** EPITECH PROJECT, 2024
** init drawable
** File description:
** init drawable
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "macro.h"
#include "my_lib.h"
#include "my_toml.h"
#include "vector.h"
#include "components.h"
#include "ecs.h"

sfVector2f sprite_size(sfTexture *text, sfVector2f size)
{
    double original_x = pow(sfTexture_getSize(text).x, -1);
    double original_y = pow(sfTexture_getSize(text).y, -1);

    return (sfVector2f){size.x * original_x, size.y * original_y};
}

static int init_sprite(sfSprite *sprite, sfTexture *texture, obj_t *obj)
{
    char *file_path = (char *)pull_data(obj, "DRAW_TEXTURE");
    int *size_x = (int *)pull_data(obj, "DRAW_SIZE_X");
    int *size_y = (int *)pull_data(obj, "DRAW_SIZE_Y");

    if (!file_path || !size_x || !size_y)
        return EXIT_ERROR;
    texture = sfTexture_createFromFile(file_path, NULL);
    if (texture == NULL)
        return EXIT_ERROR;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, sprite_size(texture,
        (sfVector2f){(float)*size_x, (float)*size_y}));
    return EXIT_SUCCESS;
}

int init_component_draw(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_draw_t *new = NULL;
    sfTexture *texture = NULL;
    sfSprite *sprite = NULL;

    if (init_sprite(sprite, texture, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    new = calloc(sizeof(c_draw_t), 1);
    new->sprite = sprite;
    new->texture = texture;
    es->components[type].data = push_index_vector(es->components[type].data,
        new, sizeof(c_draw_t), entity);
    if (!es->components[type].data)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
