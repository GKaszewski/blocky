#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"

bool is_colliding(f32 x1, f32 y1, f32 w1, f32 h1, f32 x2, f32 y2, f32 w2,
                  f32 h2);

bool is_on_floor(f32 x, f32 y, f32 width, f32 height, f32 floor_x, f32 floor_y,
                 f32 floor_width);

CollisionDirection get_collision_direction(f32 x1, f32 y1, f32 w1, f32 h1,
                                           f32 x2, f32 y2, f32 w2, f32 h2);

#endif