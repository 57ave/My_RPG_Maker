/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_toml
*/

#include "stddef.h"

#ifndef MY_TOML_H_
    #define MY_TOML_H_

typedef enum type_e {
    INT = 0,
    CHAR_PTR
} type_t;

    #define SIZE_MENU 2

typedef struct data_s {
    void *data;
    char *name;
    char type;
} data_t;

typedef struct obj_s {
    char *obj_name;
    data_t **data;
    size_t obj_size;
} obj_t;

char **read_file(char *filepath);

obj_t **get_object(char **content, int *line_offset, obj_t **obj);

data_t *get_data_struct(char *line);

void *pull_data(obj_t *obj, char *data_name);

void free_obj(obj_t **obj);

void free_data(data_t **data);

#endif /* !MY_TOML_H_ */
