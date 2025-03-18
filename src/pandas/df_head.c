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

    if (!dataframe || nb_rows <= 0 || nb_rows > dataframe->nb_rows)
        return NULL;
    data_cpy = cpy_instance(dataframe, 0,
                dataframe->nb_rows - (dataframe->nb_rows - nb_rows));
    if (!data_cpy)
        return NULL;
    return data_cpy;
}
