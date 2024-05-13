/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launcher
*/

#pragma once

    #include <SFML/Graphics.h>
    #include "ecs.h"

    #define HEIGHT_WINDOW 1080
    #define WIDTH_WINDOW 1920
    #define WIDTH_VIEW 400
    #define HEIGHT_VIEW 225

int env_verification(char **env);

int launcher(char **env);
void system_loop(sfRenderWindow *wnd, entity_system_t *es);
void event_loop(sfRenderWindow *wnd, sfEvent *event, entity_system_t *es);
