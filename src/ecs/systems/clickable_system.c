/*
** EPITECH PROJECT, 2024
** damage_system
** File description:
** damage_system
*/

#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include "clickable_component.h"
#include "draw_component.h"
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "position_component.h"

static bool is_mouse_on_entity(c_position_t *pos, c_draw_t *draw,
    sfVector2f mouse_pos)
{
    if (mouse_pos.x >= pos->pos.x
        && mouse_pos.x <= pos->pos.x + draw->size.x
        && mouse_pos.y >= pos->pos.y
        && mouse_pos.y <= pos->pos.y + draw->size.y)
        return true;
    return false;
}

void clickable_entities(entity_system_t *es, sfVector2f mouse_pos)
{
    entity_filter_t *clickable = filter_entities(3, es, POSITION,
        CLICKABLE, DRAW);
    c_position_t *pos = NULL;
    c_draw_t *draw = NULL;
    c_clickable_t *click = NULL;

    for (int i = 0; i < clickable->number; i++) {
        pos = get_comp(es, POSITION, clickable->indexes[i]);
        draw = get_comp(es, DRAW, clickable->indexes[i]);
        click = get_comp(es, CLICKABLE, clickable->indexes[i]);
        if (!is_mouse_on_entity(pos, draw, mouse_pos))
            continue;
        click->state = CLICKED;
        click->on_click(es, clickable->indexes[i]);
        break;
    }
    free_filter(clickable);
}
