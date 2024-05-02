/*
** EPITECH PROJECT, 2024
** drawing system
** File description:
** drawing system
*/

#include <SFML/Graphics.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"

void sort_by_pos(entity_filter_t *filter, vec_t *component)
{
    int tmp = 0;
    c_position_t *first = NULL;
    c_position_t *second = NULL;

    for (int i = 0; i < filter->number - 1; ++i) {
        first = (c_position_t *)
            ((void **)component->data)[filter->indexes[i]];
        second = (c_position_t *)
            ((void **)component->data)[filter->indexes[i + 1]];
        if ((int)first->pos.y > (int)second->pos.y) {
            tmp = filter->indexes[i];
            filter->indexes[i] = filter->indexes[i + 1];
            filter->indexes[i + 1] = tmp;
            sort_by_pos(filter, component);
            return;
        }
    }
}

void draw_entities(entity_system_t *es, sfRenderWindow *wnd)
{
    entity_filter_t *filter = filter_entities(2, es, DRAW, POSITION);
    vec_t *component_draw = (vec_t *)(es->components[DRAW]);
    vec_t *component_position = (vec_t *)(es->components[POSITION]);
    c_draw_t *tmp_draw = NULL;
    c_position_t *tmp_pos = NULL;

    sort_by_pos(filter, component_position);
    for (int i = 0; i < filter->number; ++i) {
        tmp_draw = (c_draw_t *)
            ((void **)component_draw->data)[filter->indexes[i]];
        tmp_pos = (c_position_t *)
            ((void **)component_position->data)[filter->indexes[i]];
        sfSprite_setPosition(tmp_draw->sprite, tmp_pos->pos);
        sfRenderWindow_drawSprite(wnd, tmp_draw->sprite, NULL);
    }
    free_filter(filter);
}
