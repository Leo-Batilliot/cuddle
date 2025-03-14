/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** copy_instance
*/

#include "my.h"

static int cpy_top_struct(dataframe_t *data_cpy,
    dataframe_t *dataframe, int size)
{
    data_cpy->nb_columns = dataframe->nb_columns;
    data_cpy->nb_rows = size;
    data_cpy->column_names = malloc(sizeof(char *) *
        (data_cpy->nb_columns + 1));
    if (!data_cpy->column_names)
        return -1;
    for (int i = 0; i < data_cpy->nb_columns
        && dataframe->column_names[i]; i++) {
        data_cpy->column_names[i] = strdup(dataframe->column_names[i]);
        if (!data_cpy->column_names[i])
            return -1;
    }
    data_cpy->column_names[dataframe->nb_columns] = NULL;
    data_cpy->column_types = malloc(sizeof(int) * data_cpy->nb_columns);
    data_cpy->data = malloc(sizeof(void **) * (size + 1));
    if (!data_cpy->data || !data_cpy->column_types)
        return -1;
    return 0;
}

static void update_type(int k, dataframe_t *dataframe, dataframe_t *data_cpy)
{
    if (dataframe->column_types[k] == INT)
        data_cpy->column_types[k] = INT;
    if (dataframe->column_types[k] == UINT)
        data_cpy->column_types[k] = UINT;
    if (dataframe->column_types[k] == BOOL)
        data_cpy->column_types[k] = BOOL;
    if (dataframe->column_types[k] == FLOAT)
        data_cpy->column_types[k] = FLOAT;
    if (dataframe->column_types[k] == STRING)
        data_cpy->column_types[k] = STRING;
}

static int fill_data(dataframe_t *dataframe, int i, dataframe_t *data_cpy,
    int cpy_index)
{
    size_t size = 0;

    for (int k = 0; k < dataframe->nb_columns && dataframe->data[i][k]; k++) {
        update_type(k, dataframe, data_cpy);
        size = strlen((char *)dataframe->data[i][k]) + 1;
        data_cpy->data[cpy_index][k] = malloc(size);
        if (!data_cpy->data[cpy_index][k])
            return -1;
        memcpy(data_cpy->data[cpy_index][k], dataframe->data[i][k], size);
    }
    return 0;
}

static int cpy_data(dataframe_t *dataframe, dataframe_t *data_cpy,
    int index)
{
    for (int i = 0; i < data_cpy->nb_rows && dataframe->data[i]; index++) {
        data_cpy->data[i] = malloc(sizeof(void *) *
            data_cpy->nb_columns);
        if (!data_cpy->data[i])
            return -1;
        if (fill_data(dataframe, index, data_cpy, i) == -1)
            return -1;
        i++;
    }
    data_cpy->data[data_cpy->nb_rows] = NULL;
    return 0;
}

dataframe_t *cpy_instance(dataframe_t *dataframe, int start_index, int size)
{
    dataframe_t *data_cpy = malloc(sizeof(dataframe_t));

    if (!dataframe || !data_cpy)
        return NULL;
    if (cpy_top_struct(data_cpy, dataframe, size) == -1)
        return NULL;
    if (cpy_data(dataframe, data_cpy, start_index) == -1)
        return NULL;
    return data_cpy;
}
