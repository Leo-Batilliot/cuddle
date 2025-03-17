/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_apply
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static int update_int(dataframe_t *new_df, int k, int i)
{
    if (new_df->column_types[i] == INT)
        if (asprintf(&(new_df->strings[k][i]),
            "%i", *(int *)new_df->data[k][i]) == -1)
            return -1;
    if (new_df->column_types[i] == UINT)
        if (asprintf(&(new_df->strings[k][i]),
            "%u", *(unsigned int *)new_df->data[k][i]) == -1)
            return -1;
    return 0;
}

static int update_strings(dataframe_t *new_df,
    dataframe_t *dataframe, int k, int i)
{
    if (new_df->column_types[i] == UNDEFINED)
        return -1;
    free(new_df->strings[k][i]);
    if (update_int(new_df, k, i) == -1)
        return -1;
    if (new_df->column_types[i] == FLOAT)
        if (asprintf(&(new_df->strings[k][i]),
            "%f", *(float *)new_df->data[k][i]) == -1)
            return -1;
    if (new_df->column_types[i] == BOOL || new_df->column_types[i] == STRING) {
        new_df->strings[k][i] = my_strdup(dataframe->strings[k][i]);
        if (!new_df)
            return -1;
    }
    return 0;
}

static int compare_column(dataframe_t *new_df, int i,
    dataframe_t *dataframe, void *(*apply_func)(void *value))
{
    for (int k = 0; k < new_df->nb_rows; k++) {
        new_df->data[k][i] = apply_func(new_df->data[k][i]);
        if (update_strings(new_df, dataframe, k, i) == -1)
            return -1;
    }
    return 0;
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    int res = 0;
    dataframe_t *new_df = NULL;

    if (!dataframe)
        return NULL;
    new_df = cpy_instance(dataframe, 0, dataframe->nb_rows);
    if (!new_df)
        return NULL;
    for (int i = 0; i < new_df->nb_columns && new_df->column_names[i]; i++) {
        if (!strcmp(new_df->column_names[i], column)) {
            res = compare_column(new_df, i, dataframe, apply_func);
            return (res == -1) ? NULL : new_df;
        }
    }
    return NULL;
}
