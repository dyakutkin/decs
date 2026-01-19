#include "direction.h"
#include "entity.h"

typedef struct
{
    enum
    {
        ACTION_TAG_SUBJECT,
        ACTION_TAG_OBJECT,
        ACTION_TAG_DIRECTION,
    } tag;
    union
    {
        struct
        {
            enum
            {
                SUBJECT_ACTION_DIE,
            } action;
        } subject;
        struct
        {
            enum
            {
                OBJECT_ACTION_EAT,
            } action;
            Entity value;
        } object;
        struct
        {
            enum
            {
                DIRECTION_ACTION_MOVE,
            } action;
            Direction value;
        } direction;
    } value;
} Action;
