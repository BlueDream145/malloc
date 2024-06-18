/*
** EPITECH PROJECT, 2019
** malloc.c
** File description:
** malloc
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/lib.h"

static block_t *startBlock = NULL;

void free(void *ptr)
{
    block_t *curr = startBlock;
    int val = 0;

    if (ptr == NULL)
        return;
    while (curr) {
        if (curr->address == ptr)
            val = 1;
        if (curr->address == ptr && free_block(curr) == NULL)
            startBlock = NULL;
        if (val == 1)
            return;
        curr = curr->next;
    }
}

void show_alloc_mem()
{
    block_t *block = startBlock;

    while (block) {
        if (block->free)
            printf("%p - %p : %u bytes\n", block->address,
                block->address + block->position, (int)block->position);
        block = block->next;
    }
}

void *realloc(void *ptr, size_t size)
{
    void *dest = malloc(size);
    block_t *end;
    block_t *start;

    if (!dest) {
        free(ptr);
        return (NULL);
    }
    else {
        end = find_block_equal(startBlock, ptr);
        start = find_block_equal(startBlock, dest);
        if (!end || !start)
            return (dest);
        else {
            copy_block(start, end);
            free(ptr);
            return (dest);
        }
    }
    return (NULL);
}

void *malloc(size_t size)
{
    block_t *currentBlock;

    if (!size)
        return (NULL);
    if (startBlock == NULL) {
        if ((startBlock = create_memory_block(size)) == NULL)
            return (NULL);
        return (startBlock->address);
    }
    currentBlock = find_block(size, startBlock);
    if (currentBlock) {
        currentBlock->free = false;
        return (currentBlock->address);
    } else {
        currentBlock = create_block(size, startBlock);
        if (!currentBlock)
            return (NULL);
        return (currentBlock->address);
    }
    return (NULL);
}