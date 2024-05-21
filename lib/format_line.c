/*
** EPITECH PROJECT, 2024
** format argument
** File description:
** so each index of the returned char ** is a command argument
*/

#include <stdlib.h>
#include <stdbool.h>

static int is_it_in_the_string(const char *string, char c)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == c)
            return true;
    }
    return false;
}

static int get_number_of_letters(char *line, int index,
    const char *separators, const char *ignorer)
{
    char tmp = '\0';
    int count = 0;

    for (int i = index; line[i] != '\0' &&
        (!is_it_in_the_string(separators, line[i]) || tmp != '\0'); i++) {
        if (tmp == '\0' && is_it_in_the_string(ignorer, line[i])) {
            tmp = line[i];
            continue;
        }
        if (tmp == line[i]) {
            tmp = '\0';
            continue;
        }
        if (line[i] == '\\' && line[i + 1] != '\0')
            i++;
        count++;
    }
    return count;
}

static int fill_the_string(char *line, char *str,
    const char *separators, const char *ignorer)
{
    char tmp = '\0';
    int i;
    int j = 0;

    for (i = 0; line[i] != '\0' &&
        (!is_it_in_the_string(separators, line[i]) || tmp != '\0'); i++) {
        if (tmp == '\0' && is_it_in_the_string(ignorer, line[i])) {
            tmp = line[i];
            continue;
        }
        if (tmp == line[i]) {
            tmp = '\0';
            continue;
        }
        if (line[i] == '\\' && line[i + 1] != '\0')
            i++;
        str[j] = line[i];
        j++;
    }
    return i;
}

static bool fill_the_array(char *line,
    char **array, const char *separators, const char *ignorer)
{
    int nb_of_letters;
    int i = 0;

    while (line[i] != '\0' && is_it_in_the_string(separators, line[i]))
        i++;
    if (line[i] == '\0')
        return true;
    nb_of_letters = get_number_of_letters(line, i, separators, ignorer);
    array[0] = calloc(sizeof(char), (nb_of_letters + 1));
    if (*array == NULL)
        return false;
    i += fill_the_string(line + i, array[0], separators, ignorer);
    return fill_the_array(line + i, array + 1, separators, ignorer);
}

static int check_char(char *tmp, char *line, const char *ignorer, int i)
{
    if (*tmp == '\0' && is_it_in_the_string(ignorer, line[i])) {
        *tmp = line[i];
        return 1;
        }
    if (*tmp == line[i]) {
        *tmp = '\0';
        return 1;
        }
    if (line[i] == '\\' && line[i + 1] != '\0') {
        return 2;
    }
    return 1;
}

static int get_number_of_argument(char *line, const char *separators,
    const char *ignorer, int count)
{
    int i = 0;
    char tmp = '\0';

    while (line[i] != '\0' && is_it_in_the_string(separators, line[i])) {
        i++;
    }
    if (line[i] == '\0')
        return count;
    while (line[i] != '\0' &&
        (!is_it_in_the_string(separators, line[i]) || tmp != '\0')) {
        i += check_char(&tmp, line, ignorer, i);
    }
    return get_number_of_argument(line + i, separators, ignorer, count + 1);
}

char **format_line(char *line, const char *separators, const char *ignorer)
{
    int nb_of_arguments;
    char **array;

    if (line == NULL)
        return NULL;
    nb_of_arguments = get_number_of_argument(line, separators, ignorer, 0);
    array = calloc(sizeof(char *), (nb_of_arguments + 1));
    if (array == NULL)
        return NULL;
    if (!fill_the_array(line, array, separators, ignorer))
        return NULL;
    return array;
}
