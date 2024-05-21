/*
** EPITECH PROJECT, 2024
** functions
** File description:
** functions
*/

#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    #include "floor/floor_struct.h"
    #include "floor/floor_case_struct.h"

tailed_t **init_floor_possibilities(void);
floor_t ***get_map(tailed_t **possibilities, char const *const path);
char **get_char_map(char const *const path);
sfVector2f sprite_size(sfTexture *text, sfVector2f size);
void draw_floor(sfRenderWindow *wnd, floor_t ***floor);


#endif /* !FUNCTIONS_H */
