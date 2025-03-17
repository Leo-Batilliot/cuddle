/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_write_csv
*/
#include "my.h"

void print_value(FILE *fd, void *value, column_type_t type)
{
    if (type == BOOL || type == STRING) {
        fprintf(fd, "%s", (char *) value);
        return;
    }
    if (type == INT) {
        fprintf(fd, "%d", *(int *) value);
        return;
    }
    if (type == UINT) {
        fprintf(fd, "%u", *(unsigned int *) value);
        return;
    }
    if (type == FLOAT) {
        fprintf(fd, "%f", *(float *) value);
        return;
    }
}

static int gest_inside(int i, FILE *fd, dataframe_t *dataframe)
{
    for (int k = 0; k < dataframe->nb_columns
        && dataframe->data[i][k]; k++) {
        if (!dataframe->data[i][k])
            return 84;
        print_value(fd, dataframe->data[i][k], dataframe->column_types[k]);
        if (k + 1 < dataframe->nb_columns)
            fprintf(fd, "%s", dataframe->separator);
    }
    return 0;
}

static int print_file(dataframe_t *dataframe, FILE *fd)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (!dataframe->column_names[i])
            return 84;
        fprintf(fd, "%s", dataframe->column_names[i]);
        if (i + 1 < dataframe->nb_columns)
            fprintf(fd, "%s", dataframe->separator);
    }
    if (dataframe->data)
        fprintf(fd, "\n");
    for (int i = 0; i < dataframe->nb_rows && dataframe->data[i]; i++) {
        if (!dataframe->data[i] || gest_inside(i, fd, dataframe))
            return 84;
        if (i + 1 < dataframe->nb_rows)
            fprintf(fd, "\n");
    }
    return 0;
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *fd = NULL;
    int res = 0;

    if (!filename || !dataframe || dataframe->nb_columns <= 0)
        return 84;
    fd = try_to_open(filename, "w");
    if (!fd)
        return 84;
    res = print_file(dataframe, fd);
    fclose(fd);
    return res;
}
