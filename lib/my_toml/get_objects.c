/*
** EPITECH PROJECT, 2023
** toml_parser
** File description:
** getters
*/

#include "my_toml.h"
#include "my_lib.h"
#include "macro.h"
#include <stddef.h>
#include <stdlib.h>

int is_obj(char *line, int *idx_line)
{
    for (*idx_line = 0; line[*idx_line] != '\0'; (*idx_line)++) {
        if (line[*idx_line] != ' ' && line[*idx_line] != '[') {
            return 0;
        }
        if (line[*idx_line] == '[') {
            *idx_line += 1;
            return 1;
        }
    }
    return 0;
}

obj_t **alloc_obj(char *line, obj_t **obj, int idx, int size_obj)
{
    obj = my_realloc(
    obj, sizeof(obj_t *) * (size_obj + 1), sizeof(obj_t *) * idx);
    if (obj == NULL) {
        return NULL;
    }
    obj[idx] = malloc(sizeof(obj_t));
    if (obj[idx] == NULL) {
        return NULL;
    }
    obj[idx]->obj_name = my_strdup_delim(line, ']');
    obj[idx + 1] = NULL;
    return obj;
}

static size_t get_obj_size(char **content, int line_offset)
{
    size_t size_obj = 0;

    while (content[line_offset] != NULL) {
        if (content[line_offset][0] == '\n') {
            return size_obj;
        }
        size_obj += 1;
        line_offset += 1;
    }
    return size_obj;
}

void get_object_values(char **content, int *line_offset, obj_t *obj, int *err)
{
    size_t idx = 0;

    size_t total_size = *line_offset;

    obj->obj_size = get_obj_size(content, *line_offset);
    if (obj->obj_size == 0) {
        *err = -1;
        return;
}
    total_size += obj->obj_size;
    obj->data = malloc(sizeof(data_t *) * (obj->obj_size + 1));
    if (obj->obj_size == 0 || obj->data == NULL) {
        free(obj->obj_name);
        free(obj);
        return;
    }
    for (size_t idx_cont = *line_offset; idx_cont < total_size; idx_cont++) {
        obj->data[idx] = get_data_struct(content[idx_cont]);
        idx++;
    }
    obj->data[idx] = NULL;
}

obj_t **get_object(char **content, int *line_offset, obj_t **obj)
{
    int idx_obj = 0;
    int size_obj = 1;
    int idx_line = 0;
    int r_value = 0;

    for (; content[*line_offset] != NULL; (*line_offset) += 1) {
        if (is_obj(content[*line_offset], &idx_line)) {
            obj = alloc_obj(
            &content[*line_offset][idx_line], obj, idx_obj, size_obj);
            *line_offset += 1;
            get_object_values(content, line_offset, obj[idx_obj], &r_value);
            size_obj++;
            idx_obj++;
        }
        if (r_value == -1)
            return NULL;
    }
    return obj;
}

void free_obj(obj_t **obj)
{
    if (obj == NULL) {
        return;
    }
    for (int i = 0; obj[i] != NULL; i++) {
        free(obj[i]->obj_name);
        free_data(obj[i]->data);
    }
    free(obj);
}
