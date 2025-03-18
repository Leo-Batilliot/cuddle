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
    data->strings = NULL;
    data->data = NULL;
    return data;
}
