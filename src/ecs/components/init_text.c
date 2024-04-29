/*
** EPITECH PROJECT, 2024
** init text
** File description:
** init text_component
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <string.h>
#include "components.h"
#include "my_toml.h"
#include "vector.h"
#include "macro.h"

static c_text_t *set_text(char *content, sfFont *font, sfText *text, int size)
{
    c_text_t *new = calloc(sizeof(c_text_t), 1);

    if (!new) {
        sfFont_destroy(font);
        sfText_destroy(text);
        return NULL;
    }
    new->content = strdup(content);
    if (!new) {
        sfFont_destroy(font);
        sfText_destroy(text);
        free(new);
        return NULL;
    }
    new->font = font;
    new->text = text;
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, (unsigned int)size);
    return new;
}

static c_text_t *init_text(char *content, char *font_path, int size)
{
    sfFont *font = sfFont_createFromFile(font_path);
    sfText *text = NULL;

    if (font == NULL)
        return NULL;
    text = sfText_create();
    if (text == NULL) {
        sfFont_destroy(font);
        return NULL;
    }
    return set_text(content, font, text, size);
}

int init_component_text(entity_system_t *es,
    obj_t *obj, component_t type, int entity)
{
    c_text_t *new = NULL;
    char *text = (char *)pull_data(obj, "TEXT-CONTENT");
    char *font_path = (char *)pull_data(obj, "TEXT-FONT");
    int *size = (int *)pull_data(obj, "TEXT-SIZE");

    if (!text || !font_path)
        return EXIT_ERROR;
    new = init_text(text, font_path, *size);
    if (!new)
        return EXIT_ERROR;
    return (init_components(es, (void *)new, type, entity));
}
