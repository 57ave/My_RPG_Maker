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
#include "components.h"
#include "macro.h"
#include "launcher.h"
#include "vector.h"
#include "ecs.h"
#include "filter_entity.h"
#include "systems.h"

sfRenderWindow *init_window(char *name, int length, int higth, int frame)
{
    sfVideoMode node = {length, higth, 100};
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
    c_velocity_t *player_velocity = (c_velocity_t *)
        (((void **)(((vec_t *)
        (es->components[VELOCITY]))->data))[es->player]);

    if (event->type == sfEvtClosed) {
        sfRenderWindow_close(wnd);
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player_velocity->velocity.y -= 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player_velocity->velocity.y += 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player_velocity->velocity.x -= 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player_velocity->velocity.x += 1;
    }
}

static void reset_player_velocity(entity_system_t *es)
{
    c_velocity_t *player_velocity = (c_velocity_t *)
        (((void **)(((vec_t *)
        (es->components[VELOCITY]))->data))[es->player]);

    player_velocity->velocity.x = 0;
    player_velocity->velocity.y = 0;
}

static void start_window(entity_system_t *es)
{
    sfRenderWindow *wnd = init_window("my_rpg", 500, 500, 30);
    sfEvent event;

    while (sfRenderWindow_isOpen(wnd)) {
        move_entities(es);
        draw_entities(es, wnd);
        sfRenderWindow_display(wnd);
        sfRenderWindow_clear(wnd, sfBlack);
        reset_player_velocity(es);
        while (sfRenderWindow_pollEvent(wnd, &event)) {
            handle_event(wnd, &event, es);
        }
    }
}

static int test(void)
{
    entity_system_t *tmp = calloc(sizeof(entity_system_t), 1);

    tmp->components = calloc(sizeof(vec_t), 1);
    tmp = init_entity_system(tmp);
    if (tmp == NULL) {
        return EXIT_ERROR;
    }
    start_window(tmp);
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
