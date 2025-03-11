/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_read_csv
*/
#include "my.h"

static column_type_t is_previous_type(
    column_type_t type1, column_type_t type2, int opt)
{
    if (opt && type1 != type2)
        return STRING;
    return type2;
}

static int set_types(dataframe_t *data)
{
    column_type_t type;

    data->column_types = malloc(sizeof(column_type_t) * data->nb_columns);
    if (!data->column_types)
        return 84;
    for (int i = 0; i < data->nb_columns; i++) {
        type = UNDEFINED;
        for (int y = 0; y < data->nb_rows; y++)
            type = is_previous_type(
                type, get_type((char *) data->data[y][i]), y);
        data->column_types[i] = type;
    }
    return 0;
}

static int parse_file_data(
    FILE *file, dataframe_t *data, const char *separator, char **line)
{
    size_t size = 0;
    char **splt;

    for (int i = 0; getline(line, &size, file) != - 1; i++) {
        data->data = realloc(data->data, sizeof(void **) * (i + 2));
        data->data[i + 1] = (void **) "caca";
        data->data[i] = NULL;
        if (!data->data) {
            data->data = NULL;
            return 84;
        }
        splt = split_str(*line, separator);
        if (!splt || my_array_len((const void **) splt) != data->nb_columns) {
            free_array((void **) splt);
            return 84;
        }
        data->data[i] = (void **) splt;
        data->nb_rows++;
    }
    return 0;
}

static int parse_file(FILE *file, dataframe_t *data, const char *separator)
{
    char **splt;
    char *line = NULL;
    size_t size = 0;
    int res = 0;

    if (getline(&line, &size, file) == - 1)
        return 84;
    splt = split_str(line, separator);
    free(line);
    line = NULL;
    if (!splt)
        return 84;
    data->column_names = splt;
    for (; data->column_names[data->nb_columns]; data->nb_columns++);
    if (parse_file_data(file, data, separator, &line) || set_types(data))
        res = 84;
    free(line);
    return res;
}

dataframe_t *df_read_csv(const char *filename, char *separator)
{
    dataframe_t *data = init_data();
    FILE *fd;
    char *sep = NULL;

    if (!data)
        return NULL;
    fd = try_to_open(filename, "r");
    if (!fd)
        return free_data(data);
    sep = my_strcat(separator, NULL, " \n");
    if (!sep) {
        fclose(fd);
        return free_data(data);
    }
    if (parse_file(fd, data, sep) == 84)
        data = free_data(data);
    fclose(fd);
    free(sep);
    return data;
}
