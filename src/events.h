#pragma once

#include "direction.h"
#include "entity.h"

typedef struct
{
    Entity entity;
    // PerceptedTags tags;
} PerceptedActor;

typedef struct
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
            PerceptedActor object;
        } object;
        struct
        {
            enum
            {
                DIRECTION_EVENT_WALKS,
                DIRECTION_EVENT_BUMPS
            } event;
            Direction direction;
        } direction;
        struct
        {
            enum
            {
                STATUS_EVENT_HUNGER,
            } event;
        } status;
    } value;
} EventContent;

typedef struct
{
    PerceptedActor subject;
    EventContent content;
} Event;
