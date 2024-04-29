/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init _animation
*/

#include "macro.h"
#include "components.h"
#include "my_toml.h"

static int init_rect(c_animation_t *animation_component, obj_t *obj)
{
    int **rect = (int **) pull_data(obj, "ANIMATION-RECT");
    int i = 0;

    if (!rect) {
        return EXIT_ERROR;
    }
    for (i = 0; rect[i] != NULL; i++);
    if (i != 4) {
        return EXIT_ERROR;
    }
    animation_component->initial_rect = {
        *(rect[0]), *(rect[1]), *(rect[2]), *(rect[3])};
}

static init_animation_data(c_animation_t *animation_component, obj_t *obj)
{
    int *x_add = NULL;
    int *y_add = NULL;
    int *nb_frame = NULL;
    int *next_line_frame = NULL;

    x_add = (int *) pull_data(obj, "ANIMATION-X_ADD");
    y_add = (int *) pull_data(obj, "ANIMATION-Y_ADD");
    nb_frame = (int *) pull_data(obj, "ANIMATION-NB_FRAME");
    next_line_frame = (int *) pull_data(obj, "ANIMATION-NEXT_LINE_FRAME");
    if (!x_add || !y_add || !nb_frame || !next_line_frame)
        return EXIT_ERROR;
    *x_add = animation_component->x_add;
    *y_add = animation_component->y_add;
    *nb_frame = animation_component->nb_frame;
    *next_line_frame = animation_component->next_line_frame;
    return EXIT_SUCCESS;
}

int init_component_animation(entity_system_t *es, obj_t *obj,
    component_t type, int entity)
{
    c_animation_t *animation_component = calloc(sizeof(c_animation_t), 1);

    if (init_rect(animation_component, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    animation_component->current_rect = animation_component->initial_rect;
    if (init_animation_data(animation_component, obj) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_components(es, (void *)animation_component, type, entity) ==
        EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
