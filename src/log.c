#include "log.h"
#include "turn.h"

static char *resolve_entity_name(world *w, entity e)
{
    entity_name *en = COMPONENT(w, e, entity_name);
    if (en == NULL)
    {
        return "Unknown";
    }
    return en->name;
}

static void print_event(world *w, event_broadcast eb)
{
    if (!eb.event.set)
    {
        return;
    }

    switch (eb.event.value.kind)
    {
    case EVENT_EXISTS:
        printf("You see %s. at (%d, %d) on Turn #%zu (offset %zu)\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               eb.origin.x, eb.origin.y, eb.turn, eb.offset);
        return;
    case EVENT_DIES:
        printf("%s dies.\n",
               resolve_entity_name(w, eb.event.value.subject.entity));
        return;
    case EVENT_OWNS:
    case EVENT_COLLECTS:
        printf("%s collects %s.\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               resolve_entity_name(w, eb.event.value.object.entity));
        return;
    case EVENT_DROPS:
        printf("%s drops %s.\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               resolve_entity_name(w, eb.event.value.object.entity));
        return;
    case EVENT_EATS:
        printf("%s eats %s.\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               resolve_entity_name(w, eb.event.value.object.entity));
        return;
    case EVENT_WALKS:
        printf("%s walks %s.\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               direction_repr(eb.event.value.direction));
        return;
    case EVENT_BUMPS:
        printf("%s bumps %s on Turn #%zu (offset %zu)\n",
               resolve_entity_name(w, eb.event.value.subject.entity),
               direction_repr(eb.event.value.direction), eb.turn, eb.offset);
        return;
    }
}

void print_player_percepted_events_system(entity player, world *w, turn *t)
{
    percepted_events *pe = COMPONENT(w, player, percepted_events);
    printf("----------Turn %zu----------\n", t->next);
    for (size_t i = 0; i < pe->broadcasts.len; i++)
    {
        event_broadcast eb = pe->broadcasts.items[i];
        print_event(w, eb);
    }
}
