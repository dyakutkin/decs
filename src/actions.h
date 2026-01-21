#include "direction.h"
#include "entity.h"

enum action_kind
{
    // "subject" actions (no payload).
    ACTION_DIE = 100,

    // "object" actions.
    ACTION_EAT = 200,

    // "directional" actions.
    ACTION_MOVE = 300,
};

struct action
{
    enum action_kind kind;
    union
    {
        struct entity object;
        enum direction direction;
    } payload;
};
