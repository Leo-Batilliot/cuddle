/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strdup
*/
#include "dataframe.h"

char *my_strdup(const char *dup)
{
    int len = 0;
    char *res = NULL;

    if (!dup)
        return NULL;
    len = my_strlen(dup);
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return NULL;
    res[len] = '\0';
    for (int i = 0; i < len; i++)
        res[i] = dup[i];
    return res;
}

char *my_strndup(const char *dup, int n)
{
    char *res = NULL;

    if (n <= 0 || n > my_strlen(dup))
        return res;
    res = malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++)
        res[i] = dup[i];
    res[n] = '\0';
    return res;
}
