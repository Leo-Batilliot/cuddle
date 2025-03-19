/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** strclean
*/
#include "dataframe.h"

char *strclean(const char *str)
{
    int start = 0;
    int end = 0;

    for (; str[start] == ' ' || str[start] == '\t' || str[start] == '\n';
        start++);
    for (end = my_strlen(str) - 1; end >= 0 && (str[end] == '\t' ||
        str[end] == '\n' || str[end] == ' '); end--);
    return my_strndup(&(str[start]), end - start + 1);
}
