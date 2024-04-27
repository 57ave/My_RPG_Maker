/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** get_data
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stdlib.h>

int go_to_char_skip(char *line, int *idx, char end)
{
    while (line[*idx] != end) {
        if (line[*idx] == '\0') {
            return EXIT_ERROR;
        }
        *idx += 1;
    }
    return EXIT_SUCCESS;
}

static int get_type(char *line, int *idx)
{
    if (go_to_char_skip(line, idx, '=') == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    for (; line[*idx] != '\0'; *idx += 1) {
        if (get_type_string(line, idx) == CHAR_PTR)
            return CHAR_PTR;
        if (get_type_int(line, idx) == INT)
            return INT;
        if (get_type_tab(line, idx) == TAB)
            return TAB;
    }
    return EXIT_ERROR;
}

static void *get_data_value(char *line, int *type)
{
    if (*type == INT)
        return get_value_int(line);
    if (*type == CHAR_PTR)
        return get_value_string(line);
    if (*type == TAB)
        return get_value_tab(line, type);
    return NULL;
}

data_t *get_data_struct(char *line)
{
    data_t *data = malloc(sizeof(data_t));
    int idx = 0;

    data->name = my_strdup_delim(line, ' ');
    data->type = get_type(line, &idx);
    data->data = get_data_value(&line[idx], (int *)&data->type);
    return data;
}

void free_data(data_t **data)
{
    if (data == NULL) {
        return;
    }
    for (int j = 0; data[j] != NULL; j++) {
        free(data[j]->data);
        free(data[j]->name);
    }
    free(data);
}
