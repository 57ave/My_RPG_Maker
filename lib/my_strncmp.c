/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n) {
        if (s1[i] < s2[i]) {
            return -1;
        }
        if (s2[i] < s1[i]) {
            return 1;
        }
        if (s2[i + 1] == '\0' && s1[i + 1] == '\0') {
            return 0;
        }
        i++;
    }
    return 0;
}
