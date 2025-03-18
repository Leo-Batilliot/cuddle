/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** trim_array
*/
#include "dataframe.h"

char *correct_and_dup(char *str, column_type_t type)
{
    int i = 0;

    if (type == STRING || type == BOOL)
        return my_strdup(str);
    for (; str[i] == ' ' || str[i] == '\t' || str[i] == '\n'; i++);
    for (; str[my_strlen(str) - 1] == '\t' || str[my_strlen(str) - 1] == '\n'
        || str[my_strlen(str) - 1] == ' '; str[my_strlen(str) - 1] = '\0');
    return my_strdup(&(str[i]));
}
