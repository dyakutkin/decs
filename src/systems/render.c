#include "render.h"
#include <math.h>
#include <stdio.h>

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

#define ANIMATION_MOVE_EPS 0.5f
#define ANIMATION_MOVE_SPEED 8.0f

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

static void draw_tile(texture_desc texture_desc, Vector2 screen_pos,
                      float texture_size_px)
{
    DrawTexturePro(*texture_desc.texture,
                   (Rectangle){
                       .x = texture_desc.x * TILE_TEXTURE_SIZE,
                       .y = texture_desc.y * TILE_TEXTURE_SIZE,
                       .width = TILE_TEXTURE_SIZE,
                       .height = TILE_TEXTURE_SIZE,
                   },
                   (Rectangle){
                       .x = screen_pos.x,
                       .y = screen_pos.y,
                       .width = texture_size_px,
                       .height = texture_size_px,
                   },
                   (Vector2){.x = 0, .y = 0}, 0, RAYWHITE);
}

static texture_desc resolve_texture_desc(textures *t, sprite_type type)
{
    switch (type)
    {
    case SPRITE_PLAYER:
        return (texture_desc){.texture = &t->chars, .x = 0, .y = 0};
    case SPRITE_NPC:
        return (texture_desc){.texture = &t->chars, .x = 0, .y = 1};
    case SPRITE_GRASS:
        return (texture_desc){.texture = &t->terrain, .x = 0, .y = 0};
    case SPRITE_WALL:
        return (texture_desc){.texture = &t->terrain, .x = 0, .y = 1};
    case SPRITE_UNKNOWN:
    default:
        return (texture_desc){.texture = &t->error, .x = 0, .y = 0};
    }
}

static float map_tile_size()
{
    return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}

static bool board_vec_is_visible(board_vec vec, render_state *rs)
{
    for (size_t i = 0; i < rs->visible_tiles.len; i++)
    {
        if (board_vec_eq(vec, rs->visible_tiles.items[i]))
        {
            return true;
        }
    }
    return false;
}

void render_state_reinit(render_state *r, world *w, percepted_events *pe)
{
    float tile_size_px = map_tile_size();

    entity_sprite *es = NULL;
    entity_flags *flags = NULL;

    ACLEAR(r->actors);
    r->current_actor_idx = 0;
    ACLEAR(r->visible_tiles);

    for (size_t i = 0; i < pe->broadcasts.len; i++)
    {
        event_broadcast eb = pe->broadcasts.items[i];
        AAPPEND(r->visible_tiles, eb.origin);

        if (eb.event.kind == EVENT_NOTHING)
        {
            continue;
        }

        es = WC(w, eb.event.subject.entity, entity_sprite);
        flags = WC(w, eb.event.subject.entity, entity_flags);

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

        es->position = (Vector2){.x = eb.origin.x * tile_size_px,
                                 .y = eb.origin.y * tile_size_px};
        AAPPEND(r->actors, eb.event.subject.entity);

        switch (eb.event.kind)
        {
        case EVENT_EXISTS:
            break;
        case EVENT_WALKS:
            es->position = (Vector2){
                .x = eb.event.payload.direction.origin.x * tile_size_px,
                .y = eb.event.payload.direction.origin.y * tile_size_px};
            AAPPEND(es->animations,
                    ((sprite_animation){
                        .kind = SPRITE_ANIMATION_MOVE,
                        .payload.move.target = (Vector2){
                            .x = (eb.event.payload.direction.origin.x +
                                  board_vec_from_direction(
                                      eb.event.payload.direction.direction)
                                      .x) *
                                 tile_size_px,
                            .y = (eb.event.payload.direction.origin.y +
                                  board_vec_from_direction(
                                      eb.event.payload.direction.direction)
                                      .y) *
                                 tile_size_px}}));
            break;
        case EVENT_BUMPS:
            es->position = (Vector2){
                .x = eb.event.payload.direction.origin.x * tile_size_px,
                .y = eb.event.payload.direction.origin.y * tile_size_px};
            AAPPEND(es->animations,
                    ((sprite_animation){
                        .kind = SPRITE_ANIMATION_MOVE,
                        .payload.move.target = (Vector2){
                            .x = (eb.event.payload.direction.origin.x +
                                  board_vec_from_direction(
                                      eb.event.payload.direction.direction)
                                      .x) *
                                 tile_size_px,
                            .y = (eb.event.payload.direction.origin.y +
                                  board_vec_from_direction(
                                      eb.event.payload.direction.direction)
                                      .y) *
                                 tile_size_px}}));
            AAPPEND(
                es->animations,
                ((sprite_animation){
                    .kind = SPRITE_ANIMATION_MOVE,
                    .payload.move.target = (Vector2){
                        .x = eb.event.payload.direction.origin.x * tile_size_px,
                        .y = eb.event.payload.direction.origin.y *
                             tile_size_px}}));
            break;
        case EVENT_DIES:
        case EVENT_OWNS:
        case EVENT_COLLECTS:
        case EVENT_DROPS:
        case EVENT_EATS:
        case EVENT_NOTHING:
            break;
        }
    }
}

void draw_background(board_vec left_upper, int top_x, int top_y,
                     render_state *r, float tile_size_px,
                     draw_background_mode mode)
{
    sprite_type st;

    for (int x = left_upper.x; x < top_x; x++)
    {
        for (int y = left_upper.y; y < top_y; y++)
        {
            bool visible = board_vec_is_visible((board_vec){x, y}, r);
            if (!visible && (mode == DRAW_BACKGROUND_VISIBLE))
            {
                continue;
            }
            if (visible && (mode == DRAW_BACKGROUND_NON_VISIBLE))
            {
                continue;
            }

            if (x < 0 || y < 0)
            {
                st = SPRITE_WALL;
            }
            else
            {
                st = SPRITE_GRASS;
            }

            texture_desc desc = resolve_texture_desc(r->textures, st);

            draw_tile(desc,
                      (Vector2){.x = x * tile_size_px, .y = y * tile_size_px},
                      tile_size_px);
            if (mode == DRAW_BACKGROUND_NON_VISIBLE)
                DrawRectanglePro((Rectangle){.x = x * tile_size_px,
                                             .y = y * tile_size_px,
                                             .width = tile_size_px,
                                             .height = tile_size_px},
                                 (Vector2){0}, 0, Fade(BLACK, 0.5f));
        }
    }
}

void render_system(render_state *r, world *w, entity player)
{
    if (!valid_entity(w, player))
    {
        return;
    }
    board_situation *situation = WC(w, player, board_situation);
    if (situation->type != BOARD_SITUATION_OCCUPIER)
    {
        return;
    }
    board_vec player_pos = situation->point;

    board_vec left_upper = {
        .x = player_pos.x - PLAYER_RENDER_RADIUS,
        .y = player_pos.y - PLAYER_RENDER_RADIUS,
    };

    float tile_size_px = map_tile_size();

    r->camera->target =
        (Vector2){left_upper.x * tile_size_px, left_upper.y * tile_size_px};

    BeginMode2D(*r->camera);

    int top_x = left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
    int top_y = left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

    draw_background(left_upper, top_x, top_y, r, tile_size_px,
                    DRAW_BACKGROUND_VISIBLE);

    if (r->current_actor_idx < r->actors.len)
    {
        entity current_actor = r->actors.items[r->current_actor_idx];
        entity_sprite *es = WC(w, current_actor, entity_sprite);

        if (es->current_animation_idx < es->animations.len)
        {
            sprite_animation current_animation =
                es->animations.items[es->current_animation_idx];

            switch (current_animation.kind)
            {
            case SPRITE_ANIMATION_MOVE:
                es->position = Vector2Lerp(
                    es->position, current_animation.payload.move.target,
                    1.0f - expf(-ANIMATION_MOVE_SPEED * GetFrameTime()));
                if (Vector2Distance(es->position,
                                    current_animation.payload.move.target) <=
                    ANIMATION_MOVE_EPS)
                {
                    es->current_animation_idx++;
                }
                break;
            }
        }
        else
        {
            r->current_actor_idx++;
        }
    }

    for (size_t i = 0; i < r->actors.len; i++)
    {
        entity actor = r->actors.items[i];
        entity_sprite *actor_sprite = WC(w, actor, entity_sprite);
        texture_desc desc =
            resolve_texture_desc(r->textures, actor_sprite->type);

        draw_tile(desc, actor_sprite->position, tile_size_px);
    }

    draw_background(left_upper, top_x, top_y, r, tile_size_px,
                    DRAW_BACKGROUND_NON_VISIBLE);

    EndMode2D();
}
