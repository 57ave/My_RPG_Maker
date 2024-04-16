/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_getnbr
*/

static int is_number(char c)
{
    if ('0' <= c && c <= '9') {
        return 1;
    }
    return 0;
}

static int is_good_char(char c)
{
    if (is_number(c)) {
        return 1;
    }
    if (c == '-' || c == '+') {
        return 1;
    }
    return 0;
}

static int find_sign(char *str)
{
    int minus_count = 0;

    for (int i = 0; is_good_char(str[i]); i++) {
        if (str[i] == '-') {
            minus_count++;
        }
    }
    if (minus_count % 2) {
        return -1;
    }
    return 1;
}

static int get_start(char *str)
{
    int i = 0;

    while (!is_number(str[i]) && str[i] != '\0') {
        i++;
    }
    return i;
}

int my_getnbr(char *str)
{
    int sign = find_sign(str);
    long value = 0;
    long tmp = 0;

    for (int i = get_start(str); is_good_char(str[i]); i++) {
        value = (value + (str[i] - '0')) * 10;
        tmp = (value * sign) / 10;
        if (tmp < -2147483648 || 2147483647 < tmp) {
            return 0;
        }
    }
    return tmp;
}
