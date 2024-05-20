#include "logic.h"
#include "constants.h"
#include "objects.h"
#include "physics.h"
#include "types.h"
#include <math.h>
#include <stdio.h>

void init_game(GameState *game) {
  if (LOGS_ON) {
    printf("Initializing game...\n");
  }

  game_state_init(game);

  if (LOGS_ON) {
    printf("Game initialized!\n");
  }
}

// TODO: rewrite player logic (for now it does not work)
void update_game(GameState *game, f32 dt, bool jump_pressed, bool move_left,
                 bool move_right) {
  if (jump_pressed && game->player->on_floor) {
    f32 boost = game->player->momentum * JUMP_VELOCITY_BOOST_MULTIPLIER;
    game->player->velocity_y = JUMP_VELOCITY_BASE - boost;
    game->player->on_floor = false;
    game->player->momentum = 0.0f;
  }

  if (move_left) {
    game->player->velocity_x = -PLAYER_ACCELERATION * dt;
    if (game->player->velocity_x < -PLAYER_MAX_VELOCITY) {
      game->player->velocity_x = -PLAYER_MAX_VELOCITY;
    }
  } else if (move_right) {
    game->player->velocity_x = PLAYER_ACCELERATION * dt;
    if (game->player->velocity_x > PLAYER_MAX_VELOCITY) {
      game->player->velocity_x = PLAYER_MAX_VELOCITY;
    }
  } else {
    if (game->player->velocity_x > 0.0f) {
      game->player->velocity_x -= PLAYER_DECELERATION * dt;
      if (game->player->velocity_x < 0.0f) {
        game->player->velocity_x = 0.0f;
      }
    } else if (game->player->velocity_x < 0.0f) {
      game->player->velocity_x += PLAYER_DECELERATION * dt;
      if (game->player->velocity_x > 0.0f) {
        game->player->velocity_x = 0.0f;
      }
    }
  }

  game->player->x += game->player->velocity_x * dt;
  game->player->y += game->player->velocity_y * dt;
  game->player->velocity_y += GRAVITY * dt;

  if (game->player->x < 0.0f) {
    game->player->x = 0.0f;
    game->player->velocity_x *= -1.0f;
  } else if (game->player->x + game->player->width > SCREEN_WIDTH) {
    game->player->x = SCREEN_WIDTH - game->player->width;
    game->player->velocity_x *= -1.0f;
  }

  // collision detection
  for (i32 i = 0; i < game->floor_count; i++) {
    Floor *floor = &game->floors[i];
    CollisionDirection collision = get_collision_direction(
        game->player->x, game->player->y, game->player->width,
        game->player->height, floor->x, floor->y, floor->width, FLOOR_HEIGHT);

    if (collision == COLLISION_UP) {
      game->player->y = floor->y - game->player->height;
      game->player->velocity_y = 0.0f;
      game->player->on_floor = true;
      if (game->player->momentum < PLAYER_MAX_MOMENTUM) {
        game->player->momentum += fabs(game->player->velocity_x);
      }

      if (i > game->highest_floor) {
        game->highest_floor = i;
      }
      game->combo_count++;
    }
  }

  // update floors
  for (i32 i = 0; i < game->floor_count; i++) {
    game->floors[i].y += game->floor_speed * dt;
  }

  // check for game over conditions
  if (game->player->y > SCREEN_HEIGHT) {
    game->game_over = true;
  }

  // increase floor speed
  static f32 time_since_last_speed_increase = 0.0f;
  time_since_last_speed_increase += dt;
  if (time_since_last_speed_increase > 5.0f) {
    if (game->floor_speed < MAX_FLOOR_SPEED) {
      game->floor_speed += 0.5f;
    }
    time_since_last_speed_increase = 0.0f;
  }

  // update score
  game->score = game->highest_floor * 10 + game->combo_count * 50;
}

void game_loop(GameState *game, RenderFunction render, InputFunction input,
               f32 dt) {
  while (!game->game_over) {
    bool jump_pressed, move_left, move_right;
    input(&jump_pressed, &move_left, &move_right);
    update_game(game, dt, jump_pressed, move_left, move_right);
    render(game);
  }
}