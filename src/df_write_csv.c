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

static int print_file(dataframe_t *dataframe, FILE *fd)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        fprintf(fd, "%s", dataframe->column_names[i]);
        print_comma(i, fd, dataframe);
    }
    fprintf(fd, "\n");
    for (int i = 0; i < dataframe->nb_rows && dataframe->data[i]; i++) {
        for (int k = 0; k < dataframe->nb_columns
            && dataframe->data[i][k]; k++) {
            fprintf(fd, "%s", (char *)dataframe->data[i][k]);
            print_comma(i, fd, dataframe);
        }
        fprintf(fd, "\n");
    }
    return 0;
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *fd = NULL;
    const char *check_csv = NULL;

    if (!filename) {
        mini_printf(2, "Error with : %s.\n", filename);
        return 84;
    }
    check_csv = filename + strlen(filename) - 3;
    if (my_strcmp(check_csv, "csv")) {
        mini_printf(2, "The format of filename must be finish by [.csv]\n");
        return 84;
    }
    fd = try_to_open(filename, "w");
    if (!fd)
        return 84;
    if (dataframe->nb_columns <= 0 || dataframe->nb_rows <= 0)
        return 84;
    print_file(dataframe, fd);
    fclose(fd);
    return 0;
}
