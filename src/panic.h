#pragma once

#include <stdio.h>

#define PANIC(MESSAGE)                                                         \
    do                                                                         \
    {                                                                          \
        fprintf(stderr, (MESSAGE));                                            \
        abort();                                                               \
    } while (0)
