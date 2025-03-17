/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** copy_instance
*/

#include "my.h"

static int cpy_names(dataframe_t *data_cpy,
    dataframe_t *dataframe)
{
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
    data_cpy->data = malloc(sizeof(void **) * (data_cpy->nb_rows + 1));
    if (!data_cpy->data)
        return -1;
    data_cpy->strings = malloc(sizeof(char **) * (data_cpy->nb_rows + 1));
    if (!data_cpy->strings)
        return -1;
    data_cpy->data[data_cpy->nb_rows] = NULL;
    data_cpy->strings[data_cpy->nb_rows] = NULL;
    return 0;
}

static int fill_data(dataframe_t *dataframe,
    int src_index, dataframe_t *data_cpy, int dest_index)
{
    for (int y = 0; y < data_cpy->nb_columns &&
        dataframe->data[src_index][y]; y++) {
        data_cpy->data[dest_index][y] = convert_to_type((void *) my_strdup(
            dataframe->strings[src_index][y]), dataframe->column_types[y]);
        if (!data_cpy->data[dest_index][y])
            return -1;
        data_cpy->strings[dest_index][y] =
            strdup(dataframe->strings[src_index][y]);
        if (!data_cpy->strings[dest_index][y])
            return -1;
    }
    return 0;
}

static int cpy_data(dataframe_t *dataframe, dataframe_t *data_cpy,
    int cpy_index)
{
    for (int i = 0; cpy_index < dataframe->nb_rows && i < data_cpy->nb_rows &&
        dataframe->data[i]; cpy_index++) {
        data_cpy->data[i] =
            malloc(sizeof(void *) * (data_cpy->nb_columns + 1));
        if (!data_cpy->data[i])
            return -1;
        data_cpy->strings[i] =
            malloc(sizeof(char *) * (data_cpy->nb_columns + 1));
        if (!data_cpy->strings[i])
            return -1;
        data_cpy->data[i][data_cpy->nb_columns] = NULL;
        data_cpy->strings[i][data_cpy->nb_columns] = NULL;
        if (fill_data(dataframe, cpy_index, data_cpy, i) == -1)
            return -1;
        i++;
    }
    return 0;
}

static dataframe_t *init_data_cpy(int col, int row, dataframe_t *dataframe)
{
    dataframe_t *data = malloc(sizeof(dataframe_t));

    if (!data)
        return NULL;
    data->nb_rows = row;
    data->nb_columns = col;
    data->column_names = NULL;
    data->strings = NULL;
    data->data = NULL;
    data->separator = dataframe->separator;
    data->column_types = malloc(sizeof(column_type_t) * data->nb_columns);
    if (!data->column_types) {
        free(data);
        return NULL;
    }
    for (int i = 0; i < data->nb_columns; i++)
        data->column_types[i] = dataframe->column_types[i];
    return data;
}

dataframe_t *cpy_instance(dataframe_t *dataframe, int start_index, int size)
{
    dataframe_t *data_cpy;

    if (!dataframe)
        return NULL;
    data_cpy = init_data_cpy(dataframe->nb_columns, size, dataframe);
    if (!data_cpy)
        return NULL;
    if (cpy_names(data_cpy, dataframe) == -1)
        return free_data(data_cpy);
    if (cpy_data(dataframe, data_cpy, start_index) == -1)
        return free_data(data_cpy);
    return data_cpy;
}
