/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_get_value
*/

#include "my.h"

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    if (!dataframe || row <= 0 || row > dataframe->nb_rows || !column)
        return NULL;
    for (int i = 0; dataframe->column_names[i]; i++) {
        if (!strcmp(column, dataframe->column_names[i]))
            return dataframe->data[row - 1][i];
    }
    return NULL;
}

static int fill_return(void ***to_return, int i, dataframe_t *dataframe)
{
    for (int k = 0; k < dataframe->nb_rows; k++) {
        if (!dataframe->data[k][i])
            return -1;
        (*to_return)[k] = dataframe->data[k][i];
    }
    return 0;
}

static int fill_column(void ***to_return, int i,
    const char *column, dataframe_t *dataframe)
{
    if (!strcmp(dataframe->column_names[i], column)) {
        (*to_return) = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
        if (!(*to_return))
            return -1;
        if (fill_return(to_return, i, dataframe) == -1)
            return -1;
        (*to_return)[dataframe->nb_rows] = NULL;
        return 0;
    }
    return 1;
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    void **to_return = NULL;
    int value = 0;

    if (!dataframe || !column)
        return NULL;
    for (int i = 0; dataframe->column_names[i]; i++) {
        value = fill_column(&to_return, i, column, dataframe);
        if (value != 1)
            return (value == 0) ? to_return : NULL;
    }
    return NULL;
}
