#ifndef OBJECTS_H
#define OBJECTS_H

#include "data.h"

void floor_init(Floor *floor, f32 x, f32 y, f32 width);
void player_init(Player *player, f32 x, f32 y, f32 width, f32 height);
void game_state_init(GameState *game);

Floor *floor_create(f32 x, f32 y, f32 width);

void floor_free(Floor *floor);
void player_free(Player *player);
void game_state_free(GameState *game);

#endif