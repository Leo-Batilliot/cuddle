/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_totype
*/

#include "dataframe.h"

static int check_cast(column_type_t downcast, int i, dataframe_t *cpy)
{
    if (downcast == STRING && (cpy->column_types[i] == INT
        || cpy->column_types[i] == UINT
        || cpy->column_types[i] == FLOAT))
        return -1;
    if (downcast == INT && cpy->column_types[i] == UINT)
        return -1;
    return 0;
}

static int loop_cast(int i, dataframe_t *cpy, column_type_t downcast)
{
    for (int k = 0; k < cpy->nb_rows && cpy->data[k][i]; k++) {
        free(cpy->data[k][i]);
        cpy->data[k][i] = convert_to_type(cpy->strings[k][i], downcast);
        if (update_strings(cpy, k, i) == -1)
            return -1;
    }
    return 0;
}

static dataframe_t *update_cpy(column_type_t downcast, int i,
    dataframe_t *cpy)
{
    if (check_cast(downcast, i, cpy) == -1)
        return NULL;
    cpy->column_types[i] = downcast;
    if (loop_cast(i, cpy, downcast) == -1)
        return NULL;
    return cpy;
}

dataframe_t *df_to_type(dataframe_t *dataframe,
    const char *column, column_type_t downcast)
{
    dataframe_t *cpy = NULL;

    if (!dataframe || !column || !downcast)
        return NULL;
    cpy = cpy_instance(dataframe, 0, dataframe->nb_rows);
    if (!cpy)
        return NULL;
    for (int i = 0; i < cpy->nb_columns && cpy->data[i]; i++)
        if (!my_tab_strcmp(column, cpy->column_names[i]))
            return update_cpy(downcast, i, cpy)
            == NULL ? NULL : cpy;
    return NULL;
}
