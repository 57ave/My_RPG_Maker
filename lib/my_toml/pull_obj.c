/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** pull_obj
*/

#include "my_toml.h"
#include "my_lib.h"

obj_t *pull_obj(obj_t **obj_tab, char const *name)
{
    for (int i = 0; obj_tab[i] != NULL; i++) {
        if (my_strcmp(name, obj_tab[i]->obj_name) == 0) {
            return obj_tab[i];
        }
    }
    return NULL;
}
