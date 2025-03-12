/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** data_struct
*/
#include "my.h"

dataframe_t *init_data(void)
{
    dataframe_t *data = malloc(sizeof(dataframe_t));

    if (!data)
        return NULL;
    data->nb_rows = 0;
    data->nb_columns = 0;
    data->column_names = NULL;
    data->column_types = NULL;
    data->data = NULL;
    return data;
}

void *free_data(dataframe_t *data)
{
    if (!data)
        return NULL;
    if (data->column_names) {
        for (int i = 0; data->column_names[i]; i++)
            free(data->column_names[i]);
        free(data->column_names);
    }
    if (data->column_types)
        free(data->column_types);
    if (data->data) {
        for (int i = 0; i < data->nb_rows && data->data[i]; i++)
            free_array(data->data[i]);
        free(data->data);
    }
    free(data);
    data = NULL;
    return NULL;
}
