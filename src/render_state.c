#include "render_state.h"

render_state *render_state_allocate(textures *t, Camera2D *c)
{
    render_state *r = calloc(1, sizeof(render_state));
    r->camera = c;
    r->textures = t;
    return r;
}

void render_state_deallocate(render_state *r)
{
    free(r->actors.items);
    free(r->visible_tiles.items);
    free(r);
}

static float map_tile_size()
{
    return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}

void render_state_reinit(render_state *r, world *w, percepted_events *pe)
{
    r->tile_size_px = map_tile_size();

    entity_sprite *es = NULL;
    entity_flags *flags = NULL;

    ACLEAR(r->actors);
    r->current_actor_idx = 0;
    ACLEAR(r->visible_tiles);

    for (size_t i = 0; i < pe->broadcasts.len; i++)
    {
        event_broadcast eb = pe->broadcasts.items[i];
        AAPPEND(r->visible_tiles, eb.origin);

        if (!eb.event.set)
        {
            continue;
        }

        event ev = eb.event.value;

        es = WC(w, ev.subject.entity, entity_sprite);
        flags = WC(w, ev.subject.entity, entity_flags);

        ACLEAR(es->animations);
        es->current_animation_idx = 0;

        if (FCONTAINS(flags->flags, ENTITY_FLAG_PLAYER))
        {
            es->type = SPRITE_PLAYER;
        }
        else if (FCONTAINS(flags->flags, ENTITY_FLAG_NPC))
        {
            es->type = SPRITE_NPC;
        }
        else
        {
            es->type = SPRITE_UNKNOWN;
        }

        es->position = (Vector2){.x = eb.origin.x * r->tile_size_px,
                                 .y = eb.origin.y * r->tile_size_px};
        AAPPEND(r->actors, ev.subject.entity);

        switch (ev.kind)
        {
        case EVENT_EXISTS:
            break;
        case EVENT_WALKS:
            es->position =
                (Vector2){.x = ev.payload.direction.origin.x * r->tile_size_px,
                          .y = ev.payload.direction.origin.y * r->tile_size_px};
            AAPPEND(es->animations,
                    ((sprite_animation){
                        .kind = SPRITE_ANIMATION_MOVE,
                        .payload.move.target =
                            (Vector2){.x = (ev.payload.direction.origin.x +
                                            ivec2_from_direction(
                                                ev.payload.direction.direction)
                                                .x) *
                                           r->tile_size_px,
                                      .y = (ev.payload.direction.origin.y +
                                            ivec2_from_direction(
                                                ev.payload.direction.direction)
                                                .y) *
                                           r->tile_size_px}}));
            break;
        case EVENT_BUMPS:
            es->position =
                (Vector2){.x = ev.payload.direction.origin.x * r->tile_size_px,
                          .y = ev.payload.direction.origin.y * r->tile_size_px};
            AAPPEND(es->animations,
                    ((sprite_animation){
                        .kind = SPRITE_ANIMATION_MOVE,
                        .payload.move.target =
                            (Vector2){.x = (ev.payload.direction.origin.x +
                                            ivec2_from_direction(
                                                ev.payload.direction.direction)
                                                .x) *
                                           r->tile_size_px,
                                      .y = (ev.payload.direction.origin.y +
                                            ivec2_from_direction(
                                                ev.payload.direction.direction)
                                                .y) *
                                           r->tile_size_px}}));
            AAPPEND(es->animations,
                    ((sprite_animation){.kind = SPRITE_ANIMATION_MOVE,
                                        .payload.move.target = (Vector2){
                                            .x = ev.payload.direction.origin.x *
                                                 r->tile_size_px,
                                            .y = ev.payload.direction.origin.y *
                                                 r->tile_size_px}}));
            break;
        case EVENT_DIES:
        case EVENT_OWNS:
        case EVENT_COLLECTS:
        case EVENT_DROPS:
        case EVENT_EATS:
            break;
        }
    }
}
