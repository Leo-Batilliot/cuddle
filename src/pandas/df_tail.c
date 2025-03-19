/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_tail
*/

#include "dataframe.h"

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *cpy_data = NULL;
    int size = 0;
    int start_index = 0;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    if (nb_rows > dataframe->nb_rows) {
        size = dataframe->nb_rows;
        start_index = 0;
    } else {
        size = nb_rows;
        start_index = dataframe->nb_rows - nb_rows;
    }
    cpy_data = cpy_instance(dataframe, start_index, size);
    if (!cpy_data)
        return NULL;
    return cpy_data;
}
