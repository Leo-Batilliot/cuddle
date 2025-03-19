/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_head
*/

#include "dataframe.h"

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *data_cpy = NULL;
    int size = 0;

    if (!dataframe || nb_rows <= 0)
        return NULL;
    if (nb_rows > dataframe->nb_rows)
        size = dataframe->nb_rows;
    else
        size = nb_rows;
    data_cpy = cpy_instance(dataframe, 0, size);
    if (!data_cpy)
        return NULL;
    return data_cpy;
}
