/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_lib
*/

#include <stddef.h>

#ifndef MY_LIB_H_
    #define MY_LIB_H_

void *my_memcpy(void *dest, void *src, size_t new_size, size_t old_size);

void *my_memset(void *dest, size_t size);

void *my_realloc(void *ptr, size_t new_size, size_t old_size);

void *my_calloc(size_t size);

char *my_strcat_line(char *dest, char *src);

char *my_strdup(char const *str);

char *my_strdup_delim(char *str, char delim);

int my_getnbr(char *str);

int my_strcmp(char const *s1, char const *s2);

int my_strncmp(char const *s1, char const *s2, int n);

char *int_to_ascii(int nb);

size_t my_strlen(char *str);

char **my_stwa(char *str, char *delim);

char *concat_strings(size_t num_args, ...);

#endif /* !MY_LIB_H_ */
