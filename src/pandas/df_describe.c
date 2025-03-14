/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_describe
*/
#include "my.h"

static double get_standard_derivation(double mean, dataframe_t *data, int i)
{
    double std = 0.0;
    double current = 0.0;

    for (int y = 0; y < data->nb_rows; y++) {
        current = atof((char *)data->data[y][i]);
        std += (current - mean) * (current - mean);
    }
    return sqrt(std / (float) data->nb_rows);
}

static void describe_column(dataframe_t *dataframe, int i)
{
    double mean = 0;
    double current = 0.0;
    double min = atof((char *)dataframe->data[0][i]);
    double max = atof((char *)dataframe->data[0][i]);

    for (int y = 0; y < dataframe->nb_rows; y++) {
        current = atof((char *)dataframe->data[y][i]);
        mean += current;
        if (current < min)
            min = current;
        if (current > max)
            max = current;
    }
    mean = mean / dataframe->nb_rows;
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", get_standard_derivation(mean, dataframe, i));
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
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
                describe_column(dataframe, i);
            }
}
