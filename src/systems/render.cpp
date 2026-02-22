#include "render.hpp"

#define ANIMATION_MOVE_EPS 0.9f
#define ANIMATION_MOVE_SPEED 15.0f

static void draw_tile(texture_desc texture_desc, Vector2 screen_pos,
                      float texture_size_px)
{
    screen_pos.x = roundf(screen_pos.x);
    screen_pos.y = roundf(screen_pos.y);

    DrawTextureRec(*texture_desc.texture,
                   (Rectangle){
                       .x = texture_desc.x * texture_size_px,
                       .y = texture_desc.y * texture_size_px,
                       .width = texture_size_px,
                       .height = texture_size_px,
                   },
                   screen_pos, RAYWHITE);
}

static texture_desc resolve_texture_desc(textures *t, sprite_type type)
{
    switch (type)
    {
    case SPRITE_PLAYER:
        return (texture_desc){
            .x = 0,
            .y = 0,
            .texture = &t->chars,
        };
    case SPRITE_NPC:
        return (texture_desc){
            .x = 0,
            .y = 1,
            .texture = &t->chars,
        };
    case SPRITE_GRASS:
        return (texture_desc){
            .x = 0,
            .y = 0,
            .texture = &t->terrain,
        };
    case SPRITE_WALL:
        return (texture_desc){
            .x = 0,
            .y = 1,
            .texture = &t->terrain,
        };
    case SPRITE_UNKNOWN:
    default:
        return (texture_desc){
            .x = 0,
            .y = 0,
            .texture = &t->error,
        };
    }
}

static bool board_tile_is_visible(ivec2 vec, render_state *rs)
{
    for (size_t i = 0; i < rs->visible_tiles.len; i++)
    {
        if (vec.eq(rs->visible_tiles.items[i]))
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

    for (int x = left_upper.x - BG_RENDER_RADIUS_DELTA;
         x < top_x + BG_RENDER_RADIUS_DELTA; x++)
    {
        for (int y = left_upper.y - BG_RENDER_RADIUS_DELTA;
             y < top_y + BG_RENDER_RADIUS_DELTA; y++)
        {
            bool visible = board_tile_is_visible((ivec2){x, y}, r);
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
                DrawRectangleRec((Rectangle){.x = x * tile_size_px,
                                             .y = y * tile_size_px,
                                             .width = tile_size_px,
                                             .height = tile_size_px},
                                 (Color){0, 0, 0, (unsigned char)(0.5f * 255)});
        }
    }
}

bool lerp_towards(Vector2 *moved, Vector2 towards)
{
    if (Vector2Distance(*moved, towards) <= ANIMATION_MOVE_EPS)
    {
        return false;
    }

    *moved = Vector2Lerp(
        *moved, towards,
        1.0f - expf(-ANIMATION_MOVE_SPEED * Clamp(GetFrameTime(), 0.0f, 0.1f)));
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
        entity_sprite *es = COMPONENT(w, current_actor, entity_sprite);

        if (es->current_animation_idx < es->animations.len)
        {
            sprite_animation current_animation =
                es->animations.items[es->current_animation_idx];

            switch (current_animation.kind)
            {
            case SPRITE_ANIMATION_MOVE:
                es->position = Vector2MoveTowards(
                    es->position, current_animation.payload.move.target,
                    ANIMATION_MOVE_EPS);
                if (!lerp_towards(&es->position,
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
        lerp_towards(&r->camera->target,
                     (Vector2){r->left_upper.x * r->tile_size_px,
                               r->left_upper.y * r->tile_size_px});
    }

    for (size_t i = 0; i < r->actors.len; i++)
    {
        entity actor = r->actors.items[i];
        entity_sprite *actor_sprite = COMPONENT(w, actor, entity_sprite);
        texture_desc desc =
            resolve_texture_desc(r->textures, actor_sprite->type);

        draw_tile(desc, actor_sprite->position, r->tile_size_px);
    }

    draw_background(r->left_upper, top_x, top_y, r, r->tile_size_px,
                    DRAW_BACKGROUND_NON_VISIBLE);

    EndMode2D();
}
