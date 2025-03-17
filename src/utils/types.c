/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** str_type
*/
#include "my.h"

column_type_t get_type(const char *str)
{
    if (!str)
        return UNDEFINED;
    if (is_bool(str))
        return BOOL;
    if (is_negative_int(str))
        return INT;
    if (is_unsigned_int(str))
        return UINT;
    if (is_float(str))
        return FLOAT;
    return STRING;
}
