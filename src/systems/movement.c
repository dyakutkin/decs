#include <stdio.h>

#include "../entity.h"
#include "../components.h"

#include "movement.h"

void movement_system(Board *board, GenArena *entities, AList events)
{
    for (int i = 0; i < events.len; i++)
    {
        MoveEvent event = ((MoveEvent *)events.events)[i];
        Entity *e = GenArena__get(entities, event.entity_id);
        if (e == NULL)
        {
            continue;
        }
        if (!BaseComponent__is_set(&(e->PositionComponent)))
        {
            continue;
        }

        Point current_position = {
            .x = e->PositionComponent.x,
            .y = e->PositionComponent.y,
        };
        Point new_attempted_point = {
            .x = current_position.x + event.delta.x,
            .y = current_position.y + event.delta.y,
        };

        bool collided = !Board__attempt_occupy(board, &new_attempted_point, event.entity_id);
        if (collided)
        {
            printf("%zu collided while attempting to move.\n", event.entity_id.idx_raw);
            continue;
        }

        Board__deoccupy(board, &current_position);
        e->PositionComponent.x = new_attempted_point.x;
        e->PositionComponent.y = new_attempted_point.y;
    }
}
