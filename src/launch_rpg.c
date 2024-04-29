/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launch_rpg
*/

#include <SFML/Graphics.h>
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

static void start_window(entity_system_t *es)
{
    sfRenderWindow *wnd = init_window("my_rpg", 500, 500, 30);

    while (sfRenderWindow_isOpen(wnd)) {
        draw_entities(es, wnd);
        sfRenderWindow_display(wnd);
        sfRenderWindow_clear(wnd, sfBlack);
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
