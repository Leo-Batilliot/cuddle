/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_sort
*/
#include "dataframe.h"

void sort_data(dataframe_t *df, int index[3], bool(*sort_func)(void *, void *))
{
    void *temp = NULL;

    if (sort_func(df->data[index[1]][index[0]], df->data[index[2]][index[0]]))
        for (int k = 0; k < df->nb_columns; k++) {
            temp = df->data[index[1]][k];
            df->data[index[1]][k] = df->data[index[2]][k];
            df->data[index[2]][k] = temp;
        }
}

void sort_column(dataframe_t *cpy, int col, bool(*sort_func)(void *, void *))
{
    for (int i = 0; i < cpy->nb_rows; i++)
        for (int j = 0; j < (cpy->nb_rows - 1); j++)
            sort_data(cpy, (int[3]) {col, j, j + 1}, sort_func);
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool(*sort_func)(void *, void *))
{
    dataframe_t *cpy;

    if (!dataframe || !column || !sort_func)
        return NULL;
    cpy = cpy_instance(dataframe, 0, dataframe->nb_rows);
    if (!cpy)
        return NULL;
    for (int i = 0; i < cpy->nb_columns; i++)
        if (!my_strcmp(cpy->column_names[i], column)) {
            sort_column(cpy, i, sort_func);
            break;
        }
    return cpy;
}
