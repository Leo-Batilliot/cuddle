/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_write_csv
*/

#include "my.h"

static void print_comma(int i, FILE *fd, dataframe_t *dataframe)
{
    if (i < dataframe->nb_columns - 1)
        fprintf(fd, ",");
}

static int gest_inside(int i, FILE *fd, dataframe_t *dataframe)
{
    for (int k = 0; k < dataframe->nb_columns
        && dataframe->data[i][k]; k++) {
        if (!dataframe->data[i][k])
            return 84;
        fprintf(fd, "%s", (char *)dataframe->data[i][k]);
        print_comma(i, fd, dataframe);
    }
    return 0;
}

static int print_file(dataframe_t *dataframe, FILE *fd)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (!dataframe->column_names[i])
            return 84;
        fprintf(fd, "%s", dataframe->column_names[i]);
        print_comma(i, fd, dataframe);
    }
    fprintf(fd, "\n");
    for (int i = 0; i < dataframe->nb_rows && dataframe->data[i]; i++) {
        if (!dataframe->data[i])
            return 84;
        if (gest_inside(i, fd, dataframe) == 84)
            return 84;
        fprintf(fd, "\n");
    }
    return 0;
}

static FILE *gest_file(const char *filename, dataframe_t *dataframe)
{
    FILE *fd = NULL;
    const char *check_csv = NULL;

    if (!filename) {
        mini_printf(2, "Error with : %s.\n", filename);
        return NULL;
    }
    if (!dataframe)
        return NULL;
    check_csv = filename + strlen(filename) - 3;
    if (!check_csv || my_strcmp(check_csv, "csv")) {
        mini_printf(2, "The format of filename must be finish by [.csv]\n");
        return NULL;
    }
    fd = try_to_open(filename, "w");
    if (!fd)
        return NULL;
    return fd;
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *fd = gest_file(filename, dataframe);

    if (!fd)
        return 84;
    if (dataframe->nb_columns <= 0) {
        fclose(fd);
        return 84;
    }
    if (print_file(dataframe, fd) == 84) {
        fclose(fd);
        return 84;
    }
    fclose(fd);
    return 0;
}
