/*
** EPITECH PROJECT, 2024
** system_loop
** File description:
** system_loop.c
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "components.h"
#include "macro.h"
#include "launcher.h"
#include "vector.h"
#include "ecs.h"
#include "filter_entity.h"
#include "systems.h"

static void catch_keys(entity_system_t *es)
{
    int gamemode = es->game_mode;

    for (int i = 0; es->keys[gamemode].key_map[i] != NULL; ++i) {
        if (es->keys[gamemode].key_map != NULL &&
            es->keys[gamemode].key_map[i] != NULL &&
            sfKeyboard_isKeyPressed(es->keys[gamemode].key_map[i]->key)) {
            es->keys[gamemode].key_map[i]->callback(es);
        }
    }
}

static void catch_click(entity_system_t *es, sfRenderWindow *wnd)
{
    sfVector2f mouse_pos = (sfVector2f)sfRenderWindow_mapPixelToCoords(wnd,
        sfMouse_getPositionRenderWindow(wnd), NULL);

    if (sfMouse_isButtonPressed(sfMouseLeft))
        clickable_entities(es, mouse_pos, wnd);
}

static void check_death(entity_system_t *es)
{
    if (((c_health_t *)get_comp(es, HEALTH, es->player))->current_health <= 0)
        es->game_mode = 3;
}

void system_loop(sfRenderWindow *wnd, entity_system_t *es, floor_t ***floor)
{
    catch_keys(es);
    catch_click(es, wnd);
    if (es->game_mode == 1) {
        aggro_entities(es);
        random_move_entities(es);
        spell_entities(es);
        animation_system(es);
        move_entities(es, floor);
        pick_system(es);
        warp_entities(es);
        draw_floor(wnd, floor, es);
    }
    draw_entities(es, wnd);
    if (es->game_mode == 2)
        draw_inventory(es, wnd);
    life_entities(es, wnd);
    dialogue_system(es, wnd);
    check_death(es);
}
