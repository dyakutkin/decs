#include "render_state.hpp"

render_state *render_state::allocate(::textures *t, Camera2D *c)
{
    render_state *r = (render_state *)calloc(1, sizeof(render_state));
    r->camera = c;
    r->textures = t;
    return r;
}

void render_state::deallocate()
{
    free(this->actors.items);
    free(this->visible_tiles.items);
    free(this);
}

static float map_tile_size() { return 128; }

void render_state::reinit(world *w, percepted_events *pe, entity player)
{
    if (!valid_entity(w, player))
    {
        return;
    }
    board_situation *situation = COMPONENT(w, player, board_situation);
    if (situation->type != BOARD_SITUATION_OCCUPIER)
    {
        return;
    }
    ivec2 player_pos = situation->point;

    this->left_upper = (ivec2){
        .x = player_pos.x - PLAYER_RENDER_RADIUS,
        .y = player_pos.y - PLAYER_RENDER_RADIUS,
    };

    this->tile_size_px = map_tile_size();

    entity_sprite *es = NULL;
    entity_flags *flags = NULL;

    DYNARRAY_CLEAR(this->actors);
    this->current_actor_idx = 0;
    DYNARRAY_CLEAR(this->visible_tiles);

    for (size_t i = 0; i < pe->broadcasts.len; i++)
    {
        event_broadcast eb = pe->broadcasts.items[i];
        DYNARRAY_APPEND(this->visible_tiles, eb.origin);

        if (!eb.event.set)
        {
            continue;
        }

        event ev = eb.event.value;

        es = COMPONENT(w, ev.subject.entity, entity_sprite);
        flags = COMPONENT(w, ev.subject.entity, entity_flags);

        DYNARRAY_CLEAR(es->animations);
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

        es->position = (Vector2){.x = eb.origin.x * this->tile_size_px,
                                 .y = eb.origin.y * this->tile_size_px};
        DYNARRAY_APPEND(this->actors, ev.subject.entity);

        switch (ev.kind)
        {
        case EVENT_EXISTS:
            break;
        case EVENT_WALKS:
            es->position = (Vector2){.x = ev.origin.x * this->tile_size_px,
                                     .y = ev.origin.y * this->tile_size_px};
            DYNARRAY_APPEND(
                es->animations,
                ((sprite_animation){
                    .kind = SPRITE_ANIMATION_MOVE,
                    .payload = {
                        .move = {
                            .target = (Vector2){
                                .x = (ev.origin.x +
                                      ivec2::from_direction(ev.direction).x) *
                                     this->tile_size_px,
                                .y = (ev.origin.y +
                                      ivec2::from_direction(ev.direction).y) *
                                     this->tile_size_px}}}}));
            break;
        case EVENT_BUMPS:
            es->position = (Vector2){.x = ev.origin.x * this->tile_size_px,
                                     .y = ev.origin.y * this->tile_size_px};
            DYNARRAY_APPEND(
                es->animations,
                ((sprite_animation){
                    .kind = SPRITE_ANIMATION_MOVE,
                    .payload = {
                        .move = {
                            .target = (Vector2){
                                .x = (ev.origin.x +
                                      ivec2::from_direction(ev.direction).x) *
                                     this->tile_size_px,
                                .y = (ev.origin.y +
                                      ivec2::from_direction(ev.direction).y) *
                                     this->tile_size_px}}}}));
            DYNARRAY_APPEND(
                es->animations,
                ((sprite_animation){
                    .kind = SPRITE_ANIMATION_MOVE,
                    .payload = {
                        .move = {
                            .target = (Vector2){
                                .x = ev.origin.x * this->tile_size_px,
                                .y = ev.origin.y * this->tile_size_px}}}}));
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
