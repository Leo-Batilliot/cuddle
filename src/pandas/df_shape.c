/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_shape
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape = {0, 0};

    if (!dataframe)
        return (dataframe_shape_t){0, 0};
    shape.nb_columns = dataframe->nb_columns;
    shape.nb_rows = dataframe->nb_rows;
    return shape;
}
