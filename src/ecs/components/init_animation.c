/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init _animation
*/

#include <stdlib.h>
#include "macro.h"
#include "components.h"
#include "my_toml.h"
#include "my_lib.h"

static const char *DIRECTION_WORDS[] = {
    "LEFT",
    "UP",
    "RIGHT",
    "DOWN"
};

static int init_rect(sfIntRect *rect, obj_t *obj, char const *name)
{
    char *data_name = concat_strings(3, "ANIMATION-", name, "-RECT");
    int **tmp_rect = (int **) pull_data(obj, data_name);
    int i = 0;

    if (!tmp_rect) {
        return EXIT_SUCCESS;
    }
    for (i = 0; tmp_rect[i] != NULL; i++);
    if (i != 4) {
        return EXIT_ERROR;
    }
    *rect = (sfIntRect){
        *(tmp_rect[0]), *(tmp_rect[1]), *(tmp_rect[2]), *(tmp_rect[3])};
    free(data_name);
    return EXIT_SUCCESS;
}

static int init_animation_data(struct anim_data *data,
    obj_t *obj, char const *name)
{
    int *x_add = (int *) pull_data(obj,
    concat_strings(3, "ANIMATION-", name, "-X_ADD"));
    int *y_add = (int *) pull_data(obj,
    concat_strings(3, "ANIMATION-", name, "-Y_ADD"));
    int *nb_frame = (int *) pull_data(obj,
    concat_strings(3, "ANIMATION-", name, "-NB_FRAME"));
    int *next_line_frame = (int *) pull_data(obj,
    concat_strings(3, "ANIMATION-", name, "-NEXT_LINE_FRAME"));
    int *anim_speed = (int *) pull_data(obj,
    concat_strings(3, "ANIMATION-", name, "-SPEED"));

    data->x_add = (x_add != NULL) ? *x_add : 0;
    data->y_add = (y_add != NULL) ? *y_add : 0;
    data->nb_frame = (nb_frame != NULL) ? *nb_frame : 1;
    data->next_line_frame = (next_line_frame != NULL) ? *next_line_frame : 0;
    data->current_frame = 0;
    data->speed = (anim_speed != NULL) ? *anim_speed : 0;
    if (init_rect(&(data->rect), obj, name) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int init_component_animation(entity_system_t *es, obj_t *obj,
    component_t type, int entity)
{
    c_animation_t *animation_component = calloc(sizeof(c_animation_t), 1);

    if (init_animation_data(
        &(animation_component->static_anim), obj, "STATIC")) {
        return EXIT_ERROR;
    }
    for (direction_t dir = 0; dir < END_DIRECTION; dir++) {
        if (init_animation_data(
        &(animation_component->multidir_anim[dir]), obj, DIRECTION_WORDS[dir]))
            return EXIT_ERROR;
    }
    animation_component->clock = sfClock_create();
    if (init_components(es, (void *)animation_component, type, entity) ==
        EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
