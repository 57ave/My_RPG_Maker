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
#include "floor/floor_case_struct.h"
#include "floor/floor_struct.h"
#include "functions.h"

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

static void set_view(entity_system_t *es, sfView *view)
{
    c_position_t *player_pos = (c_position_t *)
        (((void **)(((vec_t *)
        (es->components[POSITION]))->data))[es->player]);

    sfView_setCenter(view, (sfVector2f)
        {player_pos->pos.x + 25, player_pos->pos.y + 25});
}

static bool start_window(entity_system_t *es, floor_t ***floor)
{
    sfRenderWindow *wnd = init_window("my_rpg",
        WIDTH_WINDOW, HEIGHT_WINDOW, 18);
    sfView *view = sfView_createFromRect((sfFloatRect)
        {0, 0, WIDTH_VIEW, HEIGHT_VIEW});
    sfEvent event;

    if (!view || !wnd)
        return false;
    while (sfRenderWindow_isOpen(wnd)) {
        sfRenderWindow_setView(wnd, view);
        set_view(es, view);
        system_loop(wnd, es, floor);
        sfRenderWindow_display(wnd);
        sfRenderWindow_clear(wnd, sfBlack);
        event_loop(wnd, &event, es);
    }
    return true;
}

static int test(void)
{
    tailed_t **possibilities = init_floor_possibilities();
    floor_t ***floor = get_map(possibilities, "./config/map.txt");
    entity_system_t *es = calloc(sizeof(entity_system_t), 1);

    es->components = calloc(sizeof(vec_t), 1);
    es = init_entity_system(es);
    if (es == NULL) {
        return EXIT_ERROR;
    }
    if (!start_window(es, floor))
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
