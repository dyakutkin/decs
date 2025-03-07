
#include "render.h"

void render_system(Camera2D *camera, Textures *textures, Board *board, GenArena *entities,
                   EntityID player_id)
{
    Entity *player_e = GenArena__get(entities, player_id);

    assert(player_e != NULL);
    assert(BaseComponent__is_set(&player_e->PositionComponent));

    Point left_upper = {
        .x = player_e->PositionComponent.x - PLAYER_RENDER_RADIUS,
        .y = player_e->PositionComponent.y - PLAYER_RENDER_RADIUS,
    };

    float texture_size_px = map_tile_size();

    camera->target = (Vector2){left_upper.x * texture_size_px, left_upper.y * texture_size_px};

    BeginMode2D(*camera);

    int top_x = left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
    int top_y = left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

    for (int x = left_upper.x; x < top_x; x++)
    {
        for (int y = left_upper.y; y < top_y; y++)
        {
            EntityID occupier_id = {0};
            TileType tile_type;

            if (Board__get_occupier(board, &(Point){.x = x, .y = y}, &occupier_id))
            {
                Entity *occupier = (Entity *)GenArena__get(entities, occupier_id);
                assert(occupier);

                if (BaseComponent__is_set(&occupier->PlayerComponent))
                {
                    tile_type = PLAYER;
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

            draw_tile(textures, desc, (Point){.x = x, .y = y}, texture_size_px);
        }
    }

    EndMode2D();
}

static void draw_tile(Textures *textures, TextureDesc texture_desc, Point board_position,
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
                       .x = board_position.x * texture_size_px,
                       .y = board_position.y * texture_size_px,
                       .width = texture_size_px,
                       .height = texture_size_px,
                   },
                   (Vector2){.x = 0,
                             .y = 0},
                   0,
                   LIGHTGRAY);
}

static TextureDesc resolve_texture_desc(Textures *textures, TileType tile_type)
{
    switch (tile_type)
    {
    case PLAYER:
        return (TextureDesc){.texture = &textures->chars, .x = 0, .y = 0};
    case GRASS:
        return (TextureDesc){.texture = &textures->terrain, .x = 0, .y = 0};
    case WALL:
        return (TextureDesc){.texture = &textures->terrain, .x = 0, .y = 1};
    case UNKNOWN:
    default:
        return (TextureDesc){.texture = &textures->error, .x = 0, .y = 0};
    }
}

float map_tile_size()
{
    return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}
