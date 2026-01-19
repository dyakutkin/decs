#include "render.h"

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

static float map_tile_size();
static void draw_tile(TextureDesc texture_desc, BoardPoint point,
                      float texture_size_px);
static TextureDesc resolve_texture_desc(Textures *textures, TileType tile_type);

void render_system(Camera2D *camera, Textures *textures, Board *b, World *w,
                   Entity player)
{
    if (!valid_entity(w, player))
    {
        return;
    }
    BoardSituation *situation = WC(w, player, BoardSituation);
    if (situation->type != BOARD_SITUATION_OCCUPIER)
    {
        return;
    }
    BoardPoint player_pos = situation->point;

    BoardPoint left_upper = {
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
            BoardTile *tile;
            TileType tile_type;

            if (get_board_tile(b, (BoardPoint){x, y}, &tile) &&
                tile->occupier.set && valid_entity(w, tile->occupier.value))
            {
                EntityFlags *flags = WC(w, player, EntityFlags);

                if (FCONTAINS(flags->flags, ENTITY_FLAG_PLAYER))
                {
                    tile_type = PLAYER;
                }
                else if (FCONTAINS(flags->flags, ENTITY_FLAG_NPC))
                {
                    tile_type = NPC;
                }
                else
                {
                    tile_type = UNKNOWN;
                }
            }
            else if (x < 0 || y < 0)
            {
                tile_type = WALL;
            }
            else
            {
                tile_type = GRASS;
            }

            TextureDesc desc = resolve_texture_desc(textures, tile_type);

            draw_tile(desc, (BoardPoint){.x = x, .y = y}, texture_size_px);
        }
    }

    EndMode2D();
}

static void draw_tile(TextureDesc texture_desc, BoardPoint point,
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

static TextureDesc resolve_texture_desc(Textures *textures, TileType tile_type)
{
    switch (tile_type)
    {
    case PLAYER:
        return (TextureDesc){.texture = &textures->chars, .x = 0, .y = 0};
    case NPC:
        return (TextureDesc){.texture = &textures->chars, .x = 0, .y = 1};
    case GRASS:
        return (TextureDesc){.texture = &textures->terrain, .x = 0, .y = 0};
    case WALL:
        return (TextureDesc){.texture = &textures->terrain, .x = 0, .y = 1};
    case UNKNOWN:
    default:
        return (TextureDesc){.texture = &textures->error, .x = 0, .y = 0};
    }
}

static float map_tile_size()
{
    return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}
