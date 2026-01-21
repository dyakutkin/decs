#pragma once

#include "direction.h"
#include "entity.h"

struct percepted_actor
{
    struct entity entity;
    // PerceptedTags tags;
};

enum event_kind
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
};

enum event_status
{
    EVENT_STATUS_HUNGER,
};

struct event
{
    struct percepted_actor subject;
    enum event_kind kind;
    union
    {
        struct percepted_actor object;
        enum direction direction;
        enum event_status status;
    } payload;
};
