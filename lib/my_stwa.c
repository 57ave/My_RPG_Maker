/*
** EPITECH PROJECT, 2023
** bsq
** File description:
** my_stwa
*/

#include <stdlib.h>

static int is_good_char(char c, char *bad_char)
{
    for (int i = 0; bad_char[i] != '\0'; i++) {
        if (c == bad_char[i]) {
            return 0;
        }
    }
    if (c == '\0') {
        return 0;
    }
    return 1;
}

static int count_word(char *str, char *bad_char)
{
    int arr_count = 0;

    if (*str == '\0') {
        return 0;
    }
    for (int car = 0; str[car] != '\0'; car++) {
        while (!is_good_char(str[car], bad_char) && str[car] != '\0') {
            car++;
        }
        if (str[car] == '\0') {
            return arr_count;
        }
        arr_count++;
        while (is_good_char(str[car], bad_char)) {
            car++;
        }
    }
    return arr_count;
}

static int jump_to(char *src, int i_src, char *bad_char)
{
    while (!is_good_char(src[i_src], bad_char)) {
        i_src++;
    }
    return i_src;
}

static int get_word_len(char *src, int i_src, char *bad_char)
{
    int len = 0;

    if (src == NULL) {
        return 0;
    }
    i_src = jump_to(src, i_src, bad_char);
    while (is_good_char(src[i_src], bad_char)) {
        i_src++;
        len ++;
    }
    return len;
}

char **my_stwa(char *src, char *bad_char)
{
    int i_src = 0;
    int nbw = 0;
    int nb_words = count_word(src, bad_char);
    char **array = malloc(sizeof(char *) * (nb_words + 1));

    if (nb_words == 0)
        return array;
    for (int i = 0; nbw < nb_words && src[i_src] != '\0'; nbw++) {
        i_src = jump_to(src, i_src, bad_char);
        array[nbw] =
        malloc(sizeof(char) * (get_word_len(src, i_src, bad_char) + 1));
        for (i = 0; is_good_char(src[i_src], bad_char); i++) {
            array[nbw][i] = src[i_src];
            i_src++;
        }
        i_src++;
        array[nbw][i] = '\0';
    }
    array[nbw] = NULL;
    return array;
}
