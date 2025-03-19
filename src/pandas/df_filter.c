/*
** EPITECH PROJECT, 2025
** df_filter
** File description:
** df_filter
*/

#include "dataframe.h"

static void free_data_strings(dataframe_t **cpy_filter)
{
    for (int i = 0; (*cpy_filter)->strings[i]; i++) {
        for (int k = 0; (*cpy_filter)->strings[i][k]; k++)
            free((*cpy_filter)->strings[i][k]);
        free((*cpy_filter)->strings[i]);
    }
    free((*cpy_filter)->strings);
    for (int i = 0; (*cpy_filter)->data[i]; i++) {
        for (int k = 0; (*cpy_filter)->data[i][k]; k++)
            free((*cpy_filter)->data[i][k]);
        free((*cpy_filter)->data[i]);
    }
    free((*cpy_filter)->data);
    (*cpy_filter)->strings = NULL;
    (*cpy_filter)->data = NULL;
}

static int update_int(int i[3], dataframe_t **cpy_filter,
    dataframe_t *dataframe)
{
    if ((*cpy_filter)->column_types[i[1]] == INT) {
        (*cpy_filter)->data[i[2] - 1][i[1]] = malloc(sizeof(int));
        if (!(*cpy_filter)->data[i[2] - 1][i[1]])
            return -1;
        *(int *)(*cpy_filter)->data[i[2] - 1][i[1]] =
        *(int *)dataframe->data[i[0]][i[1]];
    }
    if ((*cpy_filter)->column_types[i[1]] == UINT) {
        (*cpy_filter)->data[i[2] - 1][i[1]] = malloc(sizeof(unsigned int));
        if (!(*cpy_filter)->data[i[2] - 1][i[1]])
            return -1;
        *(float *)(*cpy_filter)->data[i[2] - 1][i[1]] =
        *(unsigned int *)dataframe->data[i[0]][i[1]];
    }
    return 0;
}

static int update_data(dataframe_t **cpy_filter,
    dataframe_t *dataframe, int i[3])
{
    (*cpy_filter)->strings[i[2] - 1][i[1]] =
        my_strdup(dataframe->strings[i[0]][i[1]]);
    if (!(*cpy_filter)->strings[i[2] - 1][i[1]]
        || update_int(i, cpy_filter, dataframe) == -1)
        return -1;
    if ((*cpy_filter)->column_types[i[1]] == FLOAT) {
        (*cpy_filter)->data[i[2] - 1][i[1]] = malloc(sizeof(float));
        if (!(*cpy_filter)->data[i[2] - 1][i[1]])
            return -1;
        *(float *)(*cpy_filter)->data[i[2] - 1][i[1]] =
        *(float *)dataframe->data[i[0]][i[1]];
    }
    if ((*cpy_filter)->column_types[i[1]] == STRING
        || (*cpy_filter)->column_types[i[1]] == BOOL) {
        (*cpy_filter)->data[i[2] - 1][i[1]] =
        (void *)my_strdup((char *)dataframe->data[i[0]][i[1]]);
        if (!(*cpy_filter)->data[i[2] - 1][i[1]])
            return -1;
    }
    return 0;
}

static int do_reupdate(int *count, int k,
    dataframe_t *cpy_filter, dataframe_t *dataframe)
{
    (*count)++;
    cpy_filter->strings = realloc(cpy_filter->strings,
        ((*count) + 1) * sizeof(char **));
    cpy_filter->data = realloc(cpy_filter->data,
        ((*count) + 1) * sizeof(void **));
    cpy_filter->strings[(*count) - 1] =
        malloc(cpy_filter->nb_columns * sizeof(char *));
    cpy_filter->data[(*count) - 1] =
        malloc(cpy_filter->nb_columns * sizeof(void *));
    if (!cpy_filter->data[(*count) - 1] || !cpy_filter->strings[(*count) - 1])
        return -1;
    for (int j = 0; j < cpy_filter->nb_columns; j++)
        if (update_data(&cpy_filter, dataframe,
            (int[3]){k, j, (*count)}) == -1)
            return -1;
    cpy_filter->data[(*count)] = NULL;
    cpy_filter->strings[(*count)] = NULL;
    return 0;
}

void process_row(int *count, int k,
    dataframe_t **cpy_filter, dataframe_t *dataframe)
{
    if (do_reupdate(count, k, (*cpy_filter), dataframe) == -1)
        (*cpy_filter) = NULL;
}

dataframe_t *make_cpy_filter(dataframe_t *dataframe,
    bool (*filter_func)(void *value), int i, dataframe_t *cpy_filter)
{
    int count = 0;

    for (int k = 0; k < dataframe->nb_rows; k++) {
        if (filter_func(dataframe->data[k][i])) {
            process_row(&count, k, &cpy_filter, dataframe);
        }
    }
    return cpy_filter;
}

dataframe_t *df_filter(dataframe_t *dataframe,
    const char *column, bool (*filter_func)(void *value))
{
    dataframe_t *cpy_filter = NULL;

    if (!dataframe || !column || !filter_func)
        return NULL;
    cpy_filter = cpy_instance(dataframe, 0, dataframe->nb_rows);
    if (!cpy_filter)
        return NULL;
    free_data_strings(&cpy_filter);
    for (int i = 0; i < dataframe->nb_rows
        && dataframe->data[i]; i++) {
        if (!strcmp(column, cpy_filter->column_names[i]))
            return (make_cpy_filter(dataframe, filter_func, i, cpy_filter)
            == NULL) ? NULL : cpy_filter;
    }
    return NULL;
}
