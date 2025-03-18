/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** convert
*/
#include "dataframe.h"

static void *convert_to_other_types(char *str, column_type_t type)
{
    unsigned int *unint = NULL;
    float *flt = NULL;

    if (type == UINT) {
        unint = malloc(sizeof(unsigned int));
        if (!unint)
            return NULL;
        *unint = (unsigned int) atol(str);
        return unint;
    }
    if (type == FLOAT) {
        flt = malloc(sizeof(float));
        if (!flt)
            return NULL;
        *flt = atof(str);
        return flt;
    }
    return strdup(str);
}

void *convert_to_type(void *data, column_type_t type)
{
    char *str = (char *)data;
    void *res = NULL;
    int *intres = NULL;

    if (type == INT) {
        intres = malloc(sizeof(int));
        if (!intres)
            return NULL;
        if (type == INT)
            *intres = atoi(str);
        if (type == BOOL)
            *intres = (strcasecmp(str, "true") == 0);
        free(data);
        return intres;
    } else
        res = convert_to_other_types(str, type);
    free(data);
    return res;
}
