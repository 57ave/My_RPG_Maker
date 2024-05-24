/*
** EPITECH PROJECT, 2024
** draw floor
** File description:
** draw floor
*/

#include "floor/floor_struct.h"
#include "components.h"

static void draw_floor_line(sfRenderWindow *wnd, floor_t **floor)
{
    for (int i = 0; floor[i]; ++i) {
        if (floor[i]->sprite)
            sfRenderWindow_drawSprite(wnd, floor[i]->sprite, NULL);
    }
}

void draw_floor(sfRenderWindow *wnd, floor_t ***floor, entity_system_t *es)
{
    c_game_mode_t *mode = get_comp(es, GAME_MODE, es->player);

    if (mode->mode != es->game_mode) {
        return;
    }
    for (int i = 0; floor[i]; ++i) {
        draw_floor_line(wnd, floor[i]);
    }
}
