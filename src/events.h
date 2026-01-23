#pragma once

#include "bvec.h"
#include "direction.h"
#include "entity.h"
#include "offsets.h"

struct event_actor
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
    turn_id turn;

    struct event_actor subject;
    enum event_kind kind;
    union
    {
        struct event_actor object;
        struct
        {
            enum direction direction;
            struct board_vec origin;
        } direction;
        enum event_status status;
    } payload;
};
