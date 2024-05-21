/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animation system
*/

#include <SFML/Graphics.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"

sfIntRect get_rect_from_frame(struct anim_data *anim)
{
    anim->current_frame++;
    anim->current_frame = (anim->current_frame % anim->nb_frame);
    anim->rect.left = anim->x_add * anim->current_frame;
    if (anim->current_frame == anim->next_line_frame) {
        anim->rect.top += anim->y_add;
    }
    return anim->rect;
}

static direction_t get_dir(entity_system_t *es, entity_filter_t *filter, int i)
{
    vec_t *component_velocity = (vec_t *)(es->components[VELOCITY]);
    c_velocity_t *tmp_vel = (c_velocity_t *)
    ((void **)component_velocity->data)[filter->indexes[i]];

    if (tmp_vel->speed.x == 0 && tmp_vel->speed.y == 0)
        return END_DIRECTION;
    if (tmp_vel->speed.x == 0) {
        if (tmp_vel->speed.y > 0)
            return DOWN;
        else
            return UP;
    }
    if (tmp_vel->speed.x > 0)
        return RIGHT;
    if (tmp_vel->speed.x < 0)
        return LEFT;
    return END_DIRECTION;
}

void animation_entities(entity_system_t *es, entity_filter_t *filter)
{
    vec_t *component_draw = (vec_t *)(es->components[DRAW]);
    vec_t *component_animation = (vec_t *)(es->components[ANIMATION]);
    c_draw_t *tmp_draw = NULL;
    c_animation_t *tmp_anim = NULL;
    direction_t dir = 0;

    for (int i = 0; i < filter->number; ++i) {
        tmp_draw = (c_draw_t *)
            ((void **)component_draw->data)[filter->indexes[i]];
        tmp_anim = (c_animation_t *)
            ((void **)component_animation->data)[filter->indexes[i]];
        dir = get_dir(es, filter, i);
        if (dir == END_DIRECTION) {
            sfSprite_setTextureRect(tmp_draw->sprite,
            get_rect_from_frame(&(tmp_anim->static_anim)));
        } else {
            sfSprite_setTextureRect(tmp_draw->sprite,
            get_rect_from_frame(&(tmp_anim->multidir_anim[dir])));
        }
    }
}

void animation_system(entity_system_t *es)
{
    entity_filter_t *filter = filter_entities(2, es, DRAW, POSITION, VELOCITY, ANIMATION);

    animation_entities(es, filter);
    free_filter(filter);
}
