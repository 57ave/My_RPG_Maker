/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** get_data
*/

#include "my_toml.h"
#include "my_lib.h"
#include <stdlib.h>

static int get_type(char *line, int *idx)
{
    while (line[*idx] != '=') {
        if (line[*idx] == '\0') {
            return -1;
        }
        *idx += 1;
    }
    for (; line[*idx] != '\0'; *idx += 1) {
        if (line[*idx] == '"') {
            *idx += 1;
            return CHAR_PTR;
        }
        if (('0' <= line[*idx] && line[*idx] <= '9')
            || (line[*idx] == '-')) {
            return INT;
        }
    }
    return -1;
}

static void *get_data_value(char *line, int type)
{
    int value = 0;
    int *ptr = NULL;

    if (type == CHAR_PTR) {
        return (void *)my_strdup_delim(line, '"');
    }
    if (type == INT) {
        value = my_getnbr(line);
        ptr = malloc(sizeof(int));
        *ptr = value;
        return (void *)ptr;
    }
    return NULL;
}

data_t *get_data_struct(char *line)
{
    data_t *data = malloc(sizeof(data_t));
    int idx = 0;

    data->name = my_strdup_delim(line, ' ');
    data->type = get_type(line, &idx);
    data->data = get_data_value(&line[idx], data->type);
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
