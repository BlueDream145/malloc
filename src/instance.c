/*
** EPITECH PROJECT, 2019
** instance.c
** File description:
** instance
*/

#include <unistd.h>

#include "lib.h"

block_t *create_block(const size_t size, block_t *block)
{
    void *address;

    while (block->next)
        block = block->next;
    address = sbrk(size + sizeof(block_t));
    if (address == (void*)-1)
        return (NULL);
    block->next = address;
    block->next->address = (char *) address + sizeof(block_t);
    block->next->free = false;
    block->next->previous = block;
    block->next->next = NULL;
    block->next->position = size;
    return (block->next);
}

void *create_memory_block(size_t size)
{
    block_t *block;
    void *address = sbrk(size + sizeof(block_t));

    if (address == (void*)-1)
        return (NULL);
    block = address;
    block->address = (char *) address + sizeof(block_t);
    block->free = false;
    block->previous = NULL;
    block->next = NULL;
    block->position = size;
    return (block);
}

block_t *free_b(block_t *block)
{
    while (block->previous && block->previous->free) {
        block->previous->position += block->position + sizeof(block_t);
        block->previous->next = block->next;
        if (block->next)
            block->next->previous = block->previous;
        block = block->previous;
    }
    return (block);
}

block_t *free_block(block_t *block)
{
    block_t *curr = block;

    block->free = true;
    while (block->previous && block->previous->free) {
        block->previous->position += block->position + sizeof(block_t);
        block->previous->next = block->next;
        if (block->next)
            block->next->previous = block->previous;
        block = block->previous;
    }
    while (block->next && block->next->free) {
        block->position += block->next->position + sizeof(block_t);
        block->next->next->previous = block;
        block->next = block->next->next;
    }
    if (!block->next) {
        if (block->previous)
            block->previous->next = NULL;
        else
            curr = NULL;
        sbrk((block->position + sizeof(block_t)) * -1);
    }
    return (curr);
}