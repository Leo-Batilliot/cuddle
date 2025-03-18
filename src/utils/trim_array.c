/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** trim_array
*/
#include "dataframe.h"

char **correct_array(char **array)
{
    char *temp = NULL;
    int y = 0;

    if (!array)
        return NULL;
    for (int i = 0; array[i]; i++) {
        for (y = 0; array[i][y] == ' ' || array[i][y] == '\t'; y++);
        temp = my_strdup(array[i] + y);
        free(array[i]);
        array[i] = temp;
        for (y = my_strlen(array[i]) - 1; y >= 0 && (array[i][y] == ' '
            || array[i][y] == '\t' || array[i][y] == '\n'); y--)
            array[i][y] = '\0';
    }
    return array;
}
