/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strcmp
*/
#include "dataframe.h"

int my_strcmp(const char *str1, const char *str2)
{
    if (!str1 || !str2 || my_strlen(str1) != my_strlen(str2))
        return 84;
    for (int i = 0; str1[i] != '\0'; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return 0;
}

int my_tab_strcmp(const char *str1, const char *str2)
{
    char *cleaned_string = NULL;
    int res = 0;

    if (!str1 || !str2)
        return 84;
    if (!my_strcmp(str1, str2))
        return 0;
    cleaned_string = strclean(str2);
    if (!cleaned_string)
        return 84;
    res = my_strcmp(str1, cleaned_string);
    free(cleaned_string);
    return res;
}
