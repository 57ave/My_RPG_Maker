/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** menu_window
*/

#include "my_toml.h"
#include "macro.h"
#include "my_lib.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Rect.h"
#include <stdlib.h>

void init_win_null(win_t *win)
{
    win->win = NULL;
    win->spt = NULL;
    win->tex = NULL;
    win->button = NULL;
    win->mod = (sfVideoMode){0, 0, 0};
}

void init_button(obj_t *but_obj, button_t *button)
{
    sfIntRect texture_rect = (sfIntRect) {
        *(int *)pull_data(but_obj, "rect_left"),
        *(int *)pull_data(but_obj, "rect_top"),
        *(int *)pull_data(but_obj, "rect_width"),
        *(int *)pull_data(but_obj, "rect_height")};

    button->shape = sfRectangleShape_create();
    button->size = (sfVector2f) {
        *(int *)pull_data(but_obj, "size_x"),
        *(int *)pull_data(but_obj, "size_y")};
    button->vec_pos = (sfVector2f) {
        *(int *)pull_data(but_obj, "vector_x"),
        *(int *)pull_data(but_obj, "vector_y")};
    button->rect = (sfIntRect) {button->vec_pos.x, button->vec_pos.y
    , button->size.x, button->size.y};
    button->tex = sfTexture_createFromFile(
        (char *)pull_data(but_obj, "texture"), &texture_rect);
    sfRectangleShape_setTexture(button->shape, button->tex, sfFalse);
    sfRectangleShape_setSize(button->shape, button->size);
    sfRectangleShape_setPosition(button->shape, button->vec_pos);
}

button_t **find_buttons(obj_t **obj, button_t **buttons)
{
    int size = 1;
    int i_but = 0;

    for (int i = 0; obj[i] != NULL; i++) {
        if (my_strncmp(obj[i]->obj_name, "button", 6) == 0) {
            buttons = my_realloc(buttons, sizeof(button_t *) * (size + 1)
            , sizeof(button_t *) * (i_but + 1));
            buttons[i_but] = malloc(sizeof(button_t));
            init_button(obj[i], buttons[i_but]);
            buttons[size] = NULL;
            i_but++;
            size++;
        }
    }
    if (size == 0) {
        return NULL;
    }
    return buttons;
}

int init_win_from_toml(
    win_t *win, enemy_t ***enemy, text_t ***text, char *filepath)
{
    obj_t **obj = NULL;
    int line_offset = 0;
    char **content = read_file(filepath);

    init_win_null(win);
    if (content == NULL) {
        return EXIT_ERROR;
    }
    obj = get_object(content, &line_offset, obj);
    init_window(win, obj[WIN_OBJ]);
    win->button = find_buttons(obj, win->button);
    *enemy = init_enemy(*enemy, obj);
    *text = find_text(obj, *text);
    free_obj(obj);
    return EXIT_SUCCESS;
}
