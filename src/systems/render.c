#include "render.h"
#include <stdio.h>

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

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
    free(r);
}

static void draw_tile(texture_desc texture_desc, board_vec point,
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
                       .x = point.x * texture_size_px,
                       .y = point.y * texture_size_px,
                       .width = texture_size_px,
                       .height = texture_size_px,
                   },
                   (Vector2){.x = 0, .y = 0}, 0, LIGHTGRAY);
}

static void highlight_tile(board_vec point, Color color, float texture_size_px)
{
    DrawRectangleLinesEx(
        (Rectangle){
            .x = point.x * texture_size_px,
            .y = point.y * texture_size_px,
            .width = texture_size_px,
            .height = texture_size_px,
        },
        3.0f, color);
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

void render_system(render_state *r, board *b, world *w, entity player)
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

    float texture_size_px = map_tile_size();

    r->camera->target = (Vector2){left_upper.x * texture_size_px,
                                  left_upper.y * texture_size_px};

    BeginMode2D(*r->camera);

    int top_x = left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
    int top_y = left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

    sprite_type st;

    for (int x = left_upper.x; x < top_x; x++)
    {
        for (int y = left_upper.y; y < top_y; y++)
        {
            if (x < 0 || y < 0)
            {
                st = SPRITE_WALL;
            }
            else
            {
                st = SPRITE_GRASS;
            }

            texture_desc desc = resolve_texture_desc(r->textures, st);

            draw_tile(desc, (board_vec){.x = x, .y = y}, texture_size_px);
        }
    }

    percepted_events *pe = WC(w, player, percepted_events);
    if (pe != NULL)
    {
        entity_sprite *es = NULL;
        entity_flags *flags = NULL;

        for (size_t i = 0; i < pe->broadcasts.len; i++)
        {
            event_broadcast eb = pe->broadcasts.items[i];

            es = WC(w, eb.event.subject.entity, entity_sprite);
            flags = WC(w, eb.event.subject.entity, entity_flags);

            switch (eb.event.kind)
            {
            case EVENT_EXISTS:
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
                texture_desc desc = resolve_texture_desc(r->textures, es->type);

                draw_tile(desc, (board_vec){.x = eb.origin.x, .y = eb.origin.y},
                          texture_size_px);
                break;
            case EVENT_NOTHING:
            case EVENT_DIES:
            case EVENT_OWNS:
            case EVENT_COLLECTS:
            case EVENT_DROPS:
            case EVENT_EATS:
            case EVENT_WALKS:
            case EVENT_BUMPS:
                break;
            }
            highlight_tile(eb.origin, RED, texture_size_px);
        }
    }

    EndMode2D();
}
