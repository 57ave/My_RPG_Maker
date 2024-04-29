/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_toml
*/

#ifndef MY_TOML_H_
    #define MY_TOML_H_

    #include "stddef.h"

    #define STRING_CHAR '"'
    #define INT_CHARS "1234567890-"
    #define TAB_CHAR '{'

typedef enum type_e {
    INT = 0,
    CHAR_PTR,
    TAB,
    INT_TAB,
    CHAR_PTR_TAB
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

char **read_file(char const *filepath);

obj_t **get_object(char **content, int *line_offset, obj_t **obj);

data_t *get_data_struct(char *line);

void *pull_data(obj_t *obj, char *data_name);

obj_t *pull_obj(obj_t **obj_tab, char const *name);

void free_obj(obj_t **obj);

void free_data(data_t **data);

int get_type_string(char *line, int *idx);

char *get_value_string(char *line);

int get_type_int(char *line, int *idx);

void *get_value_int(char *line);

int get_type_tab(char *line, int *idx);

void *get_value_tab(char *line, char *type);

int go_to_char_skip(char *line, int *idx, char end);

#endif /* !MY_TOML_H_ */
