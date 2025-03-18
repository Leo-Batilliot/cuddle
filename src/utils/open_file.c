/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** open_file
*/
#include "dataframe.h"

FILE *try_to_open(const char *filename, const char *params)
{
    FILE *fd = fopen(filename, params);

    if (!fd)
        mini_printf(2, "%s", strerror(errno));
    return fd;
}
