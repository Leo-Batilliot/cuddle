/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_aggreg
*/

#include "dataframe.h"

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **values, int nb_values))
{
    (void)agg_func;
    (void)to_aggregate;
    (void)aggregate_by;
    (void)dataframe;
    return NULL;
}
