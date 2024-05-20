#include "physics.h"
#include "types.h"
#include <math.h>

bool is_colliding(f32 x1, f32 y1, f32 w1, f32 h1, f32 x2, f32 y2, f32 w2,
                  f32 h2) {
  return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

bool is_on_floor(f32 x, f32 y, f32 width, f32 height, f32 floor_x, f32 floor_y,
                 f32 floor_width) {
  return y + height >= floor_y && x + width >= floor_x &&
         x <= floor_x + floor_width;
}

CollisionDirection get_collision_direction(f32 x1, f32 y1, f32 w1, f32 h1,
                                           f32 x2, f32 y2, f32 w2, f32 h2) {
  if (!is_colliding(x1, y1, w1, h1, x2, y2, w2, h2)) {
    return COLLISION_NONE;
  }

  f32 dx = (x1 + w1 / 2) - (x2 + w2 / 2);
  f32 dy = (y1 + h1 / 2) - (y2 + h2 / 2);
  f32 width = (w1 + w2) / 2;
  f32 height = (h1 + h2) / 2;
  f32 cross_width = width * dy;
  f32 cross_height = height * dx;

  if (fabs(dx) <= width && fabs(dy) <= height) {
    if (cross_width > cross_height) {
      return cross_width > -cross_height ? COLLISION_DOWN : COLLISION_LEFT;
    } else {
      return cross_width > -cross_height ? COLLISION_RIGHT : COLLISION_UP;
    }
  }

  return COLLISION_NONE;
}