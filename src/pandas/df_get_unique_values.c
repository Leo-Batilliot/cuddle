/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_get_unique_values
*/

#include "dataframe.h"

static int gest_int(int index[3], int *is_dupli,
    dataframe_t *dataframe, void ***to_return)
{
    if (dataframe->column_types[index[0]] == INT
        && (*to_return)[index[2]]
        && *(int *)(*to_return)[index[2]]
        == *(int *)dataframe->data[index[1]][index[0]]) {
        (*is_dupli) = 1;
        return 1;
    }
    if (dataframe->column_types[index[0]] == UINT
        && (*to_return)[index[2]]
        && *(unsigned int *)(*to_return)[index[2]]
        == *(unsigned int *)dataframe->data[index[1]][index[0]]) {
        (*is_dupli) = 1;
        return 1;
    }
    return 0;
}

static int gest_float_string(int index[3], int *is_dupli,
    dataframe_t *dataframe, void ***to_return)
{
    if (dataframe->column_types[index[0]] == FLOAT
        && (*to_return)[index[2]]
        && *(float *)(*to_return)[index[2]]
        == *(float *)dataframe->data[index[1]][index[0]]) {
        (*is_dupli) = 1;
        return 1;
    }
    if ((dataframe->column_types[index[0]] == STRING
        || dataframe->column_types[index[0]] == BOOL)
        && (*to_return)[index[2]]
        && !strcmp((char *)(*to_return)[index[2]],
        dataframe->strings[index[1]][index[0]])) {
        (*is_dupli) = 1;
        return 1;
    }
    return 0;
}

static int get_dupli(dataframe_t *dataframe, int *is_dupli,
    void ***to_return, int index[3])
{
    if (gest_int(index, is_dupli, dataframe, to_return) == 1)
        return 1;
    if (gest_float_string(index, is_dupli, dataframe, to_return) == 1)
        return 1;
    return 0;
}

static int gest_count(int *count, dataframe_t
    *dataframe, int index[2], void ***to_return)
{
    int is_dupli = 0;

    for (int j = 0; j < *count; j++) {
        if (get_dupli(dataframe, &is_dupli,
            to_return, (int[3]){index[0], index[1], j}) == 1)
            return 1;
    }
    if (!is_dupli) {
        (*to_return)[*count] = dataframe->data[index[1]][index[0]];
        (*count)++;
    }
    return 0;
}

static int fill_rows(void ***to_return, int i, dataframe_t *dataframe)
{
    int count = 0;

    for (int k = 0; k < dataframe->nb_rows; k++) {
        if (!dataframe->data[k][i])
            continue;
        if (gest_count(&count, dataframe, (int[2]) {i, k}, to_return) == 1)
            continue;
    }
    (*to_return)[count] = NULL;
    return 0;
}

static int column_f(void ***to_return, int i,
    const char *column, dataframe_t *dataframe)
{
    if (!my_tab_strcmp(column, dataframe->column_names[i])) {
        (*to_return) = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
        if (!(*to_return))
            return -1;
        if (fill_rows(to_return, i, dataframe) == -1) {
            free_array(*to_return);
            return -1;
        }
        (*to_return)[dataframe->nb_rows] = NULL;
        return 0;
    }
    return 1;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    void **to_return = NULL;
    int value = 0;

    if (!dataframe || !column)
        return NULL;
    for (int i = 0; dataframe->column_names[i]; i++) {
        value = column_f(&to_return, i, column, dataframe);
        if (value != 1)
            return (value == 0) ? to_return : NULL;
    }
    return NULL;
}
