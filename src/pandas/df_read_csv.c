/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_read_csv
*/
#include "dataframe.h"

static int cast_to_types(dataframe_t *data)
{
    for (int i = 0; i < data->nb_columns; i++) {
        if (data->column_types[i] == STRING)
            continue;
        for (int y = 0; y < data->nb_rows; y++)
            data->data[y][i] = convert_to_type(data->data[y][i],
                data->column_types[i]);
    }
    return 0;
}

static int set_strings(dataframe_t *data)
{
    data->strings = malloc(sizeof(char **) * (data->nb_rows + 1));
    if (!data->strings)
        return 84;
    for (int i = 0; i < data->nb_rows; i++) {
        data->strings[i + 1] = NULL;
        data->strings[i] = malloc(sizeof(char *) * (data->nb_columns + 1));
        if (!data->strings[i])
            return 84;
        data->strings[i][data->nb_columns] = NULL;
    }
    for (int i = 0; i < data->nb_columns; i++)
        for (int y = 0; y < data->nb_rows; y++)
            data->strings[y][i] = correct_type((char *)
                data->data[y][i], data->column_types[i]);
    return 0;
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
    FILE *file, dataframe_t *data, const char *separator)
{
    size_t size = 0;
    char **splt;
    char *line = NULL;

    for (int i = 0; getline(&line, &size, file) != - 1; i++) {
        data->data = realloc(data->data, sizeof(void **) * (i + 1));
        data->data[i] = NULL;
        if (!data->data)
            return my_free((void *) line);
        splt = split_str(line, separator);
        if (!splt || my_array_len((const void **) splt) != data->nb_columns) {
            my_free((void *) line);
            return free_array((void **) splt);
        }
        data->data[i] = (void **) splt;
        data->nb_rows++;
    }
    my_free((void *) line);
    return 0;
}

static int parse_file(FILE *file, dataframe_t *data, const char *separator)
{
    char **splt = NULL;
    char *line = NULL;
    size_t size = 0;
    int temp = 0;

    if (getline(&line, &size, file) == - 1)
        temp = 84;
    if (!temp)
        splt = (split_str(line, separator));
    if (!splt)
        temp = 84;
    data->column_names = splt;
    for (; !temp && data->column_names[data->nb_columns]; data->nb_columns++);
    if (temp ||
        parse_file_data(file, data, separator) || set_types(data) ||
        set_strings(data) || cast_to_types(data))
        temp = 84;
    free(line);
    return temp;
}

dataframe_t *df_read_csv(const char *filename, char *separator)
{
    dataframe_t *data = init_data();
    FILE *fd;

    if (!data)
        return NULL;
    if (!separator)
        separator = ",";
    data->separator = separator;
    fd = try_to_open(filename, "r");
    if (!fd) {
        df_free(data);
        return NULL;
    }
    if (parse_file(fd, data, separator) == 84)
        df_free(data);
    fclose(fd);
    return data;
}
