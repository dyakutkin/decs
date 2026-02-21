#pragma once

#include "direction.h"
#include "entity.h"
#include "ivec2.h"
#include "turn.h"

typedef struct
{
    entity entity;
    // PerceptedTags tags;
} event_actor;

typedef enum
{
    // "subject" events (no payload).
    EVENT_EXISTS = 100,
    EVENT_DIES,

    // "object" events.
    EVENT_OWNS = 200,
    EVENT_COLLECTS,
    EVENT_DROPS,
    EVENT_EATS,

    // "directional" events.
    EVENT_WALKS = 300,
    EVENT_BUMPS,
} event_kind;

enum event_status
{
    EVENT_STATUS_HUNGER,
};

typedef struct
{

    event_actor subject;
    event_kind kind;

    event_actor object;
    direction direction;
    ivec2 origin;
} event;
