/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_head
*/

#include "my.h"

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *data_cpy = NULL;

    if (!dataframe) {
        mini_printf(2, "Dataframe is NULL.\n");
        return NULL;
    }
    if (nb_rows <= 0)
        return NULL;
    data_cpy = cpy_instance(dataframe);
    if (!data_cpy)
        return NULL;
    data_cpy->data[nb_rows] = NULL;
    data_cpy->nb_rows = nb_rows;
    return data_cpy;
}
