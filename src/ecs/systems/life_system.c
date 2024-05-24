/*
** EPITECH PROJECT, 2024
** life_bar_system
** File description:
** life_bar_system
*/

#include <stdbool.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void update_life_bar(c_health_t *health)
{
    sfVector2f new_health_size = health->life_bar_size;
    sfVector2f new_armor_size = health->life_bar_size;
    float percent_health = 0;
    float percent_armor = 0;

    if (health->max_health != 0 && health->current_health != 0) {
        percent_health = (health->current_health * 100.0) / health->max_health;
        new_health_size.x = (percent_health * health->life_bar_size.x) / 100.0;
    } else
        sfRectangleShape_setFillColor(health->health_rect, sfTransparent);
    if (health->max_armor != 0 && health->current_armor != 0) {
        percent_armor = (health->current_armor * 100.0) / health->max_armor;
        new_armor_size.x = (percent_armor * health->life_bar_size.x) / 100.0;
    } else
        sfRectangleShape_setFillColor(health->armor_rect, sfTransparent);
    sfRectangleShape_setSize(health->health_rect, new_health_size);
    sfRectangleShape_setSize(health->armor_rect, new_armor_size);
}

void life_entities(entity_system_t *es, sfRenderWindow *wnd)
{
    entity_filter_t *filter = filter_entities(2, es, HEALTH, POSITION);
    c_health_t *tmp_health = NULL;
    c_position_t *tmp_pos = NULL;
    sfVector2f new_pos = {0};

    for (int i = 0; i < filter->number; ++i) {
        tmp_health = get_comp(es, HEALTH, filter->indexes[i]);
        tmp_pos = get_comp(es, POSITION, filter->indexes[i]);
        new_pos = (sfVector2f){tmp_pos->pos.x, tmp_pos->pos.y - 5};
        if (tmp_health->current_health == 0)
            remove_entity(es, filter->indexes[i]);
        update_life_bar(tmp_health);
        sfRectangleShape_setPosition(tmp_health->health_rect, new_pos);
        sfRectangleShape_setPosition(tmp_health->armor_rect, new_pos);
        sfRenderWindow_drawRectangleShape(wnd, tmp_health->health_rect, NULL);
        sfRenderWindow_drawRectangleShape(wnd, tmp_health->armor_rect, NULL);
    }
    free_filter(filter);
}
