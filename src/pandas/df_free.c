/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_free
*/
#include "dataframe.h"

void free_dataframe_two(dataframe_t *dataframe)
{
    if (dataframe->strings) {
        for (int i = 0; i < dataframe->nb_rows && dataframe->strings[i]; i++)
            free_array((void **) dataframe->strings[i]);
        free(dataframe->strings);
    }
}

void df_free(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    if (dataframe->column_names) {
        for (int i = 0; dataframe->column_names[i]; i++)
            free(dataframe->column_names[i]);
        free(dataframe->column_names);
    }
    if (dataframe->column_types)
        free(dataframe->column_types);
    if (dataframe->data) {
        for (int i = 0; i < dataframe->nb_rows && dataframe->data[i]; i++)
            free_array(dataframe->data[i]);
        free(dataframe->data);
    }
    free_dataframe_two(dataframe);
    free(dataframe);
    dataframe = NULL;
}
