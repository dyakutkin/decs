#pragma once

#include "direction.h"
#include "entity.h"

struct percepted_actor
{
    struct entity entity;
    // PerceptedTags tags;
};

struct event_content
{
    enum
    {
        SUBJECT,
        OBJECT,
        DIRECTION,
        STATUS
    } tag;
    union
    {
        struct
        {
            enum
            {
                SUBJECT_EVENT_EXISTS,
                SUBJECT_EVENT_DIES
            } event;
        } subject;
        struct
        {
            enum
            {
                OBJECT_EVENT_OWNS,
                OBJECT_EVENT_COLLECTS,
                OBJECT_EVENT_DROPS,
                OBJECT_EVENT_EATS,
            } event;
            struct percepted_actor object;
        } object;
        struct
        {
            enum
            {
                DIRECTION_EVENT_WALKS,
                DIRECTION_EVENT_BUMPS
            } event;
            enum direction direction;
        } direction;
        struct
        {
            enum
            {
                STATUS_EVENT_HUNGER,
            } event;
        } status;
    } value;
};

struct event
{
    struct percepted_actor subject;
    struct event_content content;
};
