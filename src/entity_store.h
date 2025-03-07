#pragma once

#include "../collections/alist.h"
#include "../collections/genarena.h"

typedef struct
{
    AList archetypes;
} Arch;

typedef struct
{
    GenArena arena;
} EntityStore;