#pragma once

#include "entity_id.h"
#include "point.h"
#include "collections/alist.h"

typedef struct
{
    VecDelta delta;
    EntityID entity_id;
} MoveEvent;

typedef struct
{
    AList base;
    MoveEvent *elements;
} MoveEvents;