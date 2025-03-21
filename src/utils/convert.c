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
    if (type == STRING)
        return strdup(str);
    return NULL;
}

static void *convert_str_to_bool(const char *str)
{
    if (is_bool(str))
        return (void *) strdup(str);
    if ((is_negative_int(str) && atoi(str)) ||
        (is_unsigned_int(str) && atol(str)) ||
        (is_float(str) && atof(str)))
        return strdup("true");
    return strdup("false");
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
        free(data);
        return intres;
    }
    if (type == BOOL) {
        res = convert_str_to_bool(str);
        free(data);
        return res;
    }
    res = convert_to_other_types(str, type);
    free(data);
    return res;
}
