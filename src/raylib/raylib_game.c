#include "raylib_game.h"
#include "../game/constants.h"
#include "../game/objects.h"
#include <raylib.h>
#include <stdio.h>

void run_game(GameState *game) {
  bool jump_pressed = false;
  bool move_left = false;
  bool move_right = false;

  init_game(game);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "blocky");
  SetTargetFPS(60);

  f32 dt = 1.0f / 60.0f;

  while (!WindowShouldClose() && !game->game_over) {
    dt = GetFrameTime();

    if (LOGS_ON) {
      printf("dt: %f\n", dt);
    }

    input(&jump_pressed, &move_left, &move_right);
    update_game(game, dt, jump_pressed, move_left, move_right);
    render(game);
  }

  game_state_free(game);

  CloseWindow();
}

void input(bool *jump_pressed, bool *move_left, bool *move_right) {
  *jump_pressed = IsKeyPressed(KEY_SPACE);
  *move_left = IsKeyDown(KEY_A);
  *move_right = IsKeyDown(KEY_D);
}

void render(const GameState *game) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, DARKGRAY);
  DrawText(TextFormat("Highest floor: %d", game->highest_floor), 10, 40, 20,
           DARKGRAY);
  DrawText(TextFormat("Combo count: %d", game->combo_count), 10, 70, 20,
           DARKGRAY);

  for (i32 i = 0; i < game->floor_count; i++) {
    DrawRectangle(game->floors[i].x, game->floors[i].y, game->floors[i].width,
                  FLOOR_HEIGHT, DARKGRAY);
  }
  DrawRectangle(game->player->x, game->player->y, game->player->width,
                game->player->height, MAROON);

  DrawFPS(10, 100);
  // draw is on floor
  DrawText(
      TextFormat("On floor: %s", game->player->on_floor ? "true" : "false"), 10,
      130, 20, RED);
  // draw momentum
  DrawText(TextFormat("Momentum: %f", game->player->momentum), 10, 160, 20,
           RED);
  // draw velocity x
  DrawText(TextFormat("Velocity x: %f", game->player->velocity_x), 10, 190, 20,
           RED);
  // draw velocity y
  DrawText(TextFormat("Velocity y: %f", game->player->velocity_y), 10, 220, 20,
           RED);
  EndDrawing();
}