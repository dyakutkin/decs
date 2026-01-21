#include "direction.h"
#include "entity.h"

struct action
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
            struct entity value;
        } object;
        struct
        {
            enum
            {
                DIRECTION_ACTION_MOVE,
            } action;
            enum direction value;
        } direction;
    } value;
};
