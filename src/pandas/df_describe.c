/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_describe
*/
#include "my.h"

static float get_standard_derivation(
    float mean, dataframe_t *data, int i, column_type_t type)
{
    float std = 0.0;
    float current = 0.0;

    for (int y = 0; y < data->nb_rows; y++) {
        if (type == INT)
            current = *(int *) (data->data[y][i]);
        if (type == FLOAT)
            current = *(float *) (data->data[y][i]);
        if (type == UINT)
            current = *(unsigned int *) (data->data[y][i]);
        std += (current - mean) * (current - mean);
    }
    return sqrt(std / data->nb_rows);
}

static float get_min(dataframe_t *data, int i, column_type_t type)
{
    float min = 0.0;
    float current = 0.0;

    if (type == FLOAT)
        min = *(float *) (data->data[0][i]);
    if (type == INT)
        min = *(int *) (data->data[0][i]);
    if (type == UINT)
        min = *(unsigned int *) (data->data[0][i]);
    for (int y = 0; y < data->nb_rows; y++) {
        if (type == INT)
            current = *(int *) (data->data[y][i]);
        if (type == FLOAT)
            current = *(float *) (data->data[y][i]);
        if (type == UINT)
            current = *(unsigned int *) (data->data[y][i]);
        if (current < min)
            min = current;
    }
    return min;
}

static float get_max(dataframe_t *data, int i, column_type_t type)
{
    float max = 0.0;
    float current = 0.0;

    if (type == FLOAT)
        max = *(float *) (data->data[0][i]);
    if (type == INT)
        max = *(int *) (data->data[0][i]);
    if (type == UINT)
        max = *(unsigned int *) (data->data[0][i]);
    for (int y = 0; y < data->nb_rows; y++) {
        if (type == INT)
            current = *(int *) (data->data[y][i]);
        if (type == FLOAT)
            current = *(float *) (data->data[y][i]);
        if (type == UINT)
            current = *(unsigned int *) (data->data[y][i]);
        if (current > max)
            max = current;
    }
    return max;
}

static void describe_column(dataframe_t *data, int i, column_type_t type)
{
    float mean = 0;
    float current = 0.0;

    for (int y = 0; y < data->nb_rows; y++) {
        if (type == INT)
            current = *(int *) (data->data[y][i]);
        if (type == FLOAT)
            current = *(float *) (data->data[y][i]);
        if (type == UINT)
            current = *(unsigned int *) (data->data[y][i]);
        mean += current;
    }
    mean = mean / data->nb_rows;
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", get_standard_derivation(mean, data, i, type));
    printf("Min: %.2f\n", get_min(data, i, type));
    printf("Max: %.2f\n", get_max(data, i, type));
}

void df_describe(dataframe_t *dataframe)
{
    if (!dataframe || !dataframe->data || !dataframe->column_names ||
        !dataframe->column_types)
        return;
    for (int i = 0; i < dataframe->nb_columns && dataframe->column_names[i] &&
        dataframe->data[0][i]; i++)
        if (dataframe->column_types[i] == INT || dataframe->column_types[i] ==
            FLOAT || dataframe->column_types[i] == UINT) {
                printf("Column: %s\n", dataframe->column_names[i]);
                printf("Count: %i\n", dataframe->nb_rows);
                describe_column(dataframe, i, dataframe->column_types[i]);
            }
}
