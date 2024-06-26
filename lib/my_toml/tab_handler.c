/*
** EPITECH PROJECT, 2023
** my_toml
** File description:
** tab handler
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stdlib.h>

int get_type_tab(char *line, int *idx)
{
    if (line[*idx] == TAB_CHAR) {
        return TAB;
    }
    return EXIT_ERROR;
}

static int get_type_in_tab(char **line_parse, char *type)
{
    for (int i = 0; line_parse[0][i] != '\0'; i++) {
        if (get_type_int(line_parse[0], &i) == INT) {
            *type = INT_TAB;
            return EXIT_SUCCESS;
        }
        if (get_type_string(line_parse[0], &i) == CHAR_PTR) {
            *type = CHAR_PTR_TAB;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_ERROR;
}

void skip_char(char *string, int *i, char to_skip)
{
    while (string[*i] != '\0') {
        if (string[*i] != to_skip) {
            return;
        }
        (*i)++;
    }
}

static void **add_elem(void **tab, char *word, char type, int i)
{
    size_t size = (type == INT_TAB) ? sizeof(int *) : sizeof(char *);
    int idx = 0;
    int *int_tmp;

    tab = my_realloc(tab, size * (i + 2), size * (i + 1));
    if (tab == NULL) {
        return NULL;
    }
    if (type == INT_TAB) {
        int_tmp = calloc(sizeof(int), 1);
        *int_tmp = my_getnbr(word);
        tab[i] = int_tmp;
        tab[i + 1] = NULL;
    } else {
        go_to_char_skip(word, &idx, '"');
        idx++;
        tab[i] = my_strdup_delim(&word[idx], '"');
        tab[i + 1] = NULL;
    }
    return tab;
}

void *get_value_tab(char *line, char *type)
{
    void **tab = NULL;
    char **line_parse = my_stwa(line, ",");
    int i_word = 0;

    if (line_parse == NULL || line_parse[0] == NULL)
        return NULL;
    if (get_type_in_tab(line_parse, type) == EXIT_ERROR)
        return NULL;
    for (int i = 0; line_parse[i] != NULL; i++) {
        skip_char(line_parse[i], &i_word, ' ');
        if (line_parse[i][i_word] == ']')
            return tab;
        tab = add_elem(tab, &line_parse[i][i_word], *type, i);
        if (tab == NULL)
            return NULL;
        i_word = 0;
        free(line_parse[i]);
    }
    free(line_parse);
    return (void *)tab;
}
