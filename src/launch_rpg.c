/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launch_rpg
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

sfRenderWindow *init_window(char *name, int length, int hight, int frame)
{
    sfVideoMode node = {length, hight, 100};
    sfRenderWindow *wnd = NULL;

    wnd = sfRenderWindow_create(node, name, 4 | 2, NULL);
    if (wnd == NULL)
        return NULL;
    sfRenderWindow_setFramerateLimit(wnd, frame);
    return wnd;
}

static void handle_event(sfRenderWindow *wnd,
    sfEvent *event, entity_system_t *es)
{
    if (event->type == sfEvtClosed) {
        sfRenderWindow_close(wnd);
    }
}

static void catch_keys(entity_system_t *es)
{
    c_velocity_t *player_velocity = (c_velocity_t *)
        (((void **)(((vec_t *)
        (es->components[VELOCITY]))->data))[es->player]);
    sfInt64 time = (sfTime_asMicroseconds(
        sfClock_getElapsedTime(player_velocity->clock)));

    if (sfKeyboard_isKeyPressed(sfKeyD))
        player_velocity->speed.x +=
            (time * player_velocity->velocity.x) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        player_velocity->speed.x -=
            (time * player_velocity->velocity.x) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        player_velocity->speed.y -=
            (time * player_velocity->velocity.y) / 100000;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        player_velocity->speed.y +=
            (time * player_velocity->velocity.y) / 100000;
    sfClock_restart(player_velocity->clock);
}

static void set_view(entity_system_t *es, sfView *view)
{
    c_position_t *player_pos = (c_position_t *)
        (((void **)(((vec_t *)
        (es->components[POSITION]))->data))[es->player]);
    c_draw_t *player_draw = (c_draw_t *)
        (((void **)(((vec_t *)
        (es->components[DRAW]))->data))[es->player]);

    sfView_setCenter(view, (sfVector2f)
        {player_pos->pos.x + 25, player_pos->pos.y + 25});
}

static bool start_window(entity_system_t *es)
{
    sfRenderWindow *wnd = init_window("my_rpg", 1920, 1080, 18);
    sfView *view = sfView_createFromRect((sfFloatRect){0, 0, 400, 225});
    sfEvent event;

    if (!view || !wnd)
        return false;
    while (sfRenderWindow_isOpen(wnd)) {
        sfRenderWindow_setView(wnd, view);
        set_view(es, view);
        catch_keys(es);
        aggro_entities(es);
        move_entities(es);
        draw_entities(es, wnd);
        sfRenderWindow_display(wnd);
        sfRenderWindow_clear(wnd, sfBlack);
        while (sfRenderWindow_pollEvent(wnd, &event))
            handle_event(wnd, &event, es);
    }
    return true;
}

static int test(void)
{
    entity_system_t *es = calloc(sizeof(entity_system_t), 1);

    es->components = calloc(sizeof(vec_t), 1);
    es = init_entity_system(es);
    if (es == NULL) {
        return EXIT_ERROR;
    }
    if (!start_window(es))
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int launcher(char **env)
{
    if (env_verification(env) == EXIT_ERROR)
        return EXIT_ERROR;
    if (test() == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
