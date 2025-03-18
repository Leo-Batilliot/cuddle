/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** types
*/
#include "dataframe.h"
#include <float.h>
#include <limits.h>

static int not_only_spaces(const char *str, int index)
{
    for (; str[index] != '\0'; index++)
        if (str[index] != ' ' || str[index] != '\t' || str[index] != '\n')
            return 1;
    return 0;
}

int is_bool(const char *str)
{
    char *buffer;
    int res = 0;

    if (!str)
        return 0;
    buffer = my_strdup(str);
    if (!buffer)
        return 0;
    buffer = str_lowcase(buffer);
    if (!my_strcmp(buffer, "false") || !my_strcmp(buffer, "true"))
        res = 1;
    free(buffer);
    return res;
}

int get_sign(const char *str, int *index)
{
    if (!str)
        return 0;
    for (; str[*index] == ' ' || str[*index] == '\t' ||
        str[*index] == '\n'; *index += 1);
    if (str[0] == '-') {
        *index += 1;
        return - 1;
    }
    return 1;
}

int is_unsigned_int(const char *str)
{
    int index = 0;
    int sign = get_sign(str, &index);
    long res = 0;

    if (sign != 1 || str[index] > '9' || str[index] < '0')
        return 0;
    for (; str[index] != '\0'; index++) {
        if (str[index] < '0' || str[index] > '9')
            break;
        res = res * 10 + (str[index] - '0');
        if (res > UINT_MAX)
            return 0;
    }
    if (!not_only_spaces(str, index) && res >= 0 && res <= UINT_MAX)
        return 1;
    return 0;
}

int is_negative_int(const char *str)
{
    int index = 0;
    int sign = get_sign(str, &index);
    long res = 0;

    if (sign != - 1 || str[index] > '9' || str[index] < '0')
        return 0;
    for (; str[index] != '\0'; index++) {
        if (str[index] < '0' || str[index] > '9')
            return 0;
        res = res * 10 + (str[index] - '0');
        if (- res < INT_MIN)
            return 0;
    }
    res *= sign;
    if (!not_only_spaces(str, index) && res < 0 && res >= INT_MIN)
        return 1;
    return 0;
}

static int valid_decimal_part(
    const char *str, int *index, int count)
{
    if (str[*index] != '.')
        return 0;
    (*index) += 1;
    if (str[*index] == '\0')
        return 0;
    for (; str[*index] != '\0'; *index += 1) {
        if (str[*index] > '9' || str[*index] < '0')
            return 0;
        count++;
    }
    if (count > 46)
        return 0;
    return 1;
}

int is_float(const char *str)
{
    int index = 0;
    int sign = get_sign(str, &index);
    double res = 0;
    int count = 0;

    if (sign == 0 || str[index] > '9' || str[index] < '0')
        return 0;
    for (; str[index] != '\0' && str[index] != '.'; index++) {
        res = res * 10 + (str[index] - '0');
        count++;
        if (res > FLT_MAX)
            return 0;
    }
    sign = valid_decimal_part(str, &index, count) && count;
    if (sign && !not_only_spaces(str, index))
        return 1;
    return 0;
}
