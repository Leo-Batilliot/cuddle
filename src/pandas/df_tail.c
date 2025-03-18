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

    if (!dataframe || nb_rows <= 0 || nb_rows > dataframe->nb_rows)
        return NULL;
    cpy_data = cpy_instance(dataframe,
                dataframe->nb_rows - nb_rows,
                nb_rows);
    if (!cpy_data)
        return NULL;
    return cpy_data;
}
