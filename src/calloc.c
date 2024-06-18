/*
** EPITECH PROJECT, 2019
** calloc.c
** File description:
**
*/

#include <stdio.h>
#include <unistd.h>

#include "lib.h"

void *calloc(size_t nb, size_t size)
{
    int *ptr = malloc(size * nb);
    size_t s;

    if (ptr == NULL)
        return (NULL);
    for (s = 0; s < size; ++s)
        ptr[s] = 0;
    return (ptr);
}
