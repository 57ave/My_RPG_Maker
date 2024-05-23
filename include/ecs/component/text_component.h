/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** text_component.h
*/

#pragma once

typedef struct text_s {
    char *content;
    sfText *text;
    sfFont *font;
    int size;
} c_text_t;
