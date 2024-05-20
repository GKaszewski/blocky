#ifndef DATA_H
#define DATA_H

#include "types.h"

typedef struct {
  f32 x, y;
  f32 width;
} Floor;

typedef struct {
  f32 x, y;
  f32 velocity_x, velocity_y;
  f32 width, height;
  bool on_floor;
  f32 momentum;
} Player;

typedef struct {
  Floor *floors;
  i32 floor_count;
  Player *player;
  f32 floor_speed;
  i32 highest_floor;
  i32 score;
  i32 combo_count;
  bool game_over;
} GameState;

#endif