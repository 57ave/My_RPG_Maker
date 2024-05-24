/*
** EPITECH PROJECT, 2024
** event_loop.c
** File description:
** event_loop
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
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

static void handle_event(sfRenderWindow *wnd,
    sfEvent *event, entity_system_t *es)
{
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) {
        sfRenderWindow_close(wnd);
    }
    if (event->type == sfEvtMouseButtonPressed &&
        event->mouseButton.button == sfMouseLeft) {
        clickable_entities(es, (sfVector2i){event->mouseButton.x,
            event->mouseButton.y});
    }
}

void event_loop(sfRenderWindow *wnd, sfEvent *event, entity_system_t *es)
{
    while (sfRenderWindow_pollEvent(wnd, event))
        handle_event(wnd, event, es);
}
