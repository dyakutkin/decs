#include "render.h"
#include <stdio.h>

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

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

static texture_desc resolve_texture_desc(textures *t, tile_type tile_type)
{
    switch (tile_type)
    {
    case TILE_TYPE_PLAYER:
        return (texture_desc){.texture = &t->chars, .x = 0, .y = 0};
    case TILE_TYPE_NPC:
        return (texture_desc){.texture = &t->chars, .x = 0, .y = 1};
    case TILE_TYPE_GRASS:
        return (texture_desc){.texture = &t->terrain, .x = 0, .y = 0};
    case TILE_TYPE_WALL:
        return (texture_desc){.texture = &t->terrain, .x = 0, .y = 1};
    case TILE_TYPE_UNKNOWN:
    default:
        return (texture_desc){.texture = &t->error, .x = 0, .y = 0};
    }
}

static float map_tile_size()
{
    return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}

void render_system(Camera2D *camera, textures *t, board *b, world *w,
                   entity player)
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

    camera->target = (Vector2){left_upper.x * texture_size_px,
                               left_upper.y * texture_size_px};

    BeginMode2D(*camera);

    int top_x = left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
    int top_y = left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

    for (int x = left_upper.x; x < top_x; x++)
    {
        for (int y = left_upper.y; y < top_y; y++)
        {
            board_tile *tile;
            tile_type tile_type;

            if (board_get_tile(b, (board_vec){x, y}, &tile) &&
                tile->occupier.set && valid_entity(w, tile->occupier.value))
            {
                entity_flags *flags = WC(w, player, entity_flags);

                if (FCONTAINS(flags->flags, ENTITY_FLAG_PLAYER))
                {
                    tile_type = TILE_TYPE_PLAYER;
                }
                else if (FCONTAINS(flags->flags, ENTITY_FLAG_NPC))
                {
                    tile_type = TILE_TYPE_NPC;
                }
                else
                {
                    tile_type = TILE_TYPE_UNKNOWN;
                }
            }
            else if (x < 0 || y < 0)
            {
                tile_type = TILE_TYPE_WALL;
            }
            else
            {
                tile_type = TILE_TYPE_GRASS;
            }

            texture_desc desc = resolve_texture_desc(t, tile_type);

            draw_tile(desc, (board_vec){.x = x, .y = y}, texture_size_px);
        }
    }

    percepted_events *pe = WC(w, player, percepted_events);
    if (pe != NULL)
    {
        for (size_t i = 0; i < pe->broadcasts.len; i++)
        {
            event_broadcast eb = pe->broadcasts.items[i];
            highlight_tile(eb.origin, RED, texture_size_px);
        }
    }

    EndMode2D();
}
