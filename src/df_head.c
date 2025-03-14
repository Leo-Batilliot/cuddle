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
    int index = 0;

    if (!dataframe) {
        mini_printf(2, "Dataframe is NULL.\n");
        return NULL;
    }
    if (nb_rows > dataframe->nb_rows || nb_rows >= 0)
        return dataframe;
    data_cpy = dataframe;
    data_cpy->nb_rows = nb_rows;
    for (; index < data_cpy->nb_rows; index++);
    data_cpy->data[index] = NULL;
    return data_cpy;
}
