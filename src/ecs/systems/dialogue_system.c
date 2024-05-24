/*
** EPITECH PROJECT, 2024
** dialogue system
** File description:
** dalogue
*/

#include <SFML/Graphics.h>
#include <string.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"

static void print_dialogue(entity_system_t *es,
    int entity, sfRenderWindow *wnd)
{
    c_text_t *text_comp = get_comp(es, TEXT, entity);
    c_position_t *player_pos = get_comp(es, POSITION, entity);
    sfFloatRect rect = sfText_getGlobalBounds(text_comp->text);

    sfText_setPosition(text_comp->text, (sfVector2f)
        {(player_pos->pos.x - ((rect.width / 2))) + 18,
        player_pos->pos.y - 15});
    sfRenderWindow_drawText(wnd, text_comp->text, NULL);
}

void dialogue_system(entity_system_t *es, sfRenderWindow *wnd)
{
    entity_filter_t *filter = filter_entities(3,
        es, POSITION, INTERACTION_ZONE, TEXT);

    for (int i = 0; i < filter->number; ++i) {
        if (interaction_zone_entities(es, es->player, filter->indexes[i])) {
            print_dialogue(es, filter->indexes[i], wnd);
            break;
        }
    }
    free_filter(filter);
}
