#pragma once

#include "direction.h"
#include "entity.h"

typedef enum
{
    // "subject" actions (no payload).
    ACTION_DIE = 100,

    // "object" actions.
    ACTION_EAT = 200,

    // "directional" actions.
    ACTION_MOVE = 300,
} action_kind;

typedef struct
{
    action_kind kind;
    union
    {
        entity object;
        direction direction;
    } payload;
} action;
