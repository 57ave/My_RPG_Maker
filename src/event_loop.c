/*
** EPITECH PROJECT, 2024
** event_loop.c
** File description:
** event_loop
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include "components.h"
#include "key_mapping.h"
#include "macro.h"
#include "launcher.h"
#include "vector.h"
#include "ecs.h"
#include "filter_entity.h"
#include "systems.h"

static void handle_keys_event(sfEvent *event, entity_system_t *es)
{
    int gamemode = es->game_mode;

    for (int i = 0; i < KEYS_COUNT; ++i) {
        if (event->key.code == es->keys[gamemode].key_map[i]->key) {
            es->keys[gamemode].key_map[i]->callback();
        }
    }
}

static void handle_event(sfRenderWindow *wnd,
    sfEvent *event, entity_system_t *es)
{
    if (event->type == sfEvtClosed) {
        sfRenderWindow_close(wnd);
    }
    if (event->type == sfEvtKeyPressed) {
        handle_keys_event(event, es);
    }
}

void event_loop(sfRenderWindow *wnd, sfEvent *event, entity_system_t *es)
{
    while (sfRenderWindow_pollEvent(wnd, event))
        handle_event(wnd, event, es);
}
