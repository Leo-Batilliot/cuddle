/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** trim_array
*/
#include "dataframe.h"

char *correct_type(char *str, column_type_t type)
{
    if (type == STRING || type == BOOL)
        return my_strdup(str);
    return strclean(str);
}
