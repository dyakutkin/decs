#include "render.h"
#include <math.h>

#define TILE_TEXTURE_SIZE 128

#define ANIMATION_MOVE_EPS 0.9f
#define ANIMATION_MOVE_SPEED 15.0f

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

static bool ivec2_is_visible(ivec2 vec, render_state *rs)
{
    for (size_t i = 0; i < rs->visible_tiles.len; i++)
    {
        if (ivec2_eq(vec, rs->visible_tiles.items[i]))
        {
            return true;
        }
    }
    return false;
}

void draw_background(ivec2 left_upper, int top_x, int top_y, render_state *r,
                     float tile_size_px, draw_background_mode mode)
{
    sprite_type st;

    for (int x = left_upper.x; x < top_x; x++)
    {
        for (int y = left_upper.y; y < top_y; y++)
        {
            bool visible = ivec2_is_visible((ivec2){x, y}, r);
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

bool move_towards(Vector2 *moved, Vector2 towards)
{

    *moved = Vector2Lerp(*moved, towards,
                         1.0f - expf(-ANIMATION_MOVE_SPEED * GetFrameTime()));
    if (Vector2Distance(*moved, towards) <= ANIMATION_MOVE_EPS)
    {
        return false;
    }
    return true;
}

void render_system(render_state *r, world *w)
{
    BeginMode2D(*r->camera);

    int top_x = r->left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
    int top_y = r->left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

    draw_background(r->left_upper, top_x, top_y, r, r->tile_size_px,
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
                if (!move_towards(&es->position,
                                  current_animation.payload.move.target))
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
    else
    {
        move_towards(&r->camera->target,
                     (Vector2){r->left_upper.x * r->tile_size_px,
                               r->left_upper.y * r->tile_size_px});
    }

    for (size_t i = 0; i < r->actors.len; i++)
    {
        entity actor = r->actors.items[i];
        entity_sprite *actor_sprite = WC(w, actor, entity_sprite);
        texture_desc desc =
            resolve_texture_desc(r->textures, actor_sprite->type);

        draw_tile(desc, actor_sprite->position, r->tile_size_px);
    }

    draw_background(r->left_upper, top_x, top_y, r, r->tile_size_px,
                    DRAW_BACKGROUND_NON_VISIBLE);

    EndMode2D();
}
