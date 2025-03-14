/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** df_info
*/
#include "my.h"

char *type_value_to_strr(unsigned int value)
{
    char *types[] = {"bool", "int", "unsigned int", "float", "string"};

    if (value > 4)
        return "undefined";
    return types[value];
}

void df_info(dataframe_t *dataframe)
{
    if (!dataframe || !dataframe->column_names || !dataframe->column_types)
        return;
    printf("%i columns:\n", dataframe->nb_columns);
    for (int i = 0; i < dataframe->nb_columns && dataframe->column_names[i];
        i++)
        printf("- %s: %s\n", dataframe->column_names[i],
            type_value_to_strr(dataframe->column_types[i]));
}
