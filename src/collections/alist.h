#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t cap;
    size_t len;
    size_t elem_size;
} AList;

#define ALIST_APPEND(self, value)                                                             \
    do                                                                                        \
    {                                                                                         \
        AList *base = (AList *)self;                                                          \
        if (base->len == base->cap)                                                           \
        {                                                                                     \
            size_t new_cap = base->cap * 2;                                                   \
            self->elements = realloc(self->elements, base->elem_size * new_cap);              \
        }                                                                                     \
        memcpy((char *)self->elements + base->len * base->elem_size, value, base->elem_size); \
        base->len++;                                                                          \
    } while (0)

#define ALIST_FREE(self) free(self->elements)
#define ALIST_CLEAR(self) self->base.len = 0

#define ALIST_ALLOC(type, init_cap)                  \
    {                                                \
        .elements = malloc(init_cap * sizeof(type)), \
        .base = {                                    \
            .elem_size = sizeof(type),               \
            .len = 0,                                \
            .cap = init_cap,                         \
        },                                           \
    }
