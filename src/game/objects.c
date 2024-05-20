#include "objects.h"
#include "constants.h"
#include <stdlib.h>

void floor_init(Floor *floor, f32 x, f32 y, f32 width) {
  floor->x = x;
  floor->y = y;
  floor->width = width;
}

void player_init(Player *player, f32 x, f32 y, f32 width, f32 height) {
  player->x = x;
  player->y = y;
  player->width = width;
  player->height = height;
  player->velocity_x = 0.0f;
  player->velocity_y = 0.0f;
  player->momentum = 0.0f;
  player->on_floor = false;
}

void game_state_init(GameState *game) {
  Player *player = malloc(sizeof(Player));
  Floor *floor = malloc(sizeof(Floor));

  player_init(player, SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLAYER_HEIGHT,
              PLAYER_WIDTH, PLAYER_HEIGHT);
  game->player = player;

  game->floors = (Floor *)malloc(INITIAL_FLOOR_COUNT * sizeof(Floor));
  game->floor_count = INITIAL_FLOOR_COUNT;
  floor_init(&game->floors[0], 0, SCREEN_HEIGHT - FLOOR_HEIGHT, SCREEN_WIDTH);
  //   for (i32 i = 1; i < game->floor_count; i++) {
  //     f32 y = i * (SCREEN_HEIGHT / INITIAL_FLOOR_COUNT);
  //     f32 width =
  //         (i % 50 == 0)
  //             ? SCREEN_WIDTH
  //             : (rand() % (MAX_FLOOR_WIDTH - MIN_FLOOR_WIDTH) +
  //             MIN_FLOOR_WIDTH);
  //     f32 x = (i % 50 == 0) ? 0 : rand() % (SCREEN_WIDTH - (i32)width);
  //     floor_init(&game->floors[i], x, y, width);
  //   }

  game->floor_speed = 0.0f;
  game->highest_floor = 0;
  game->score = 0;
  game->combo_count = 0;
  game->game_over = false;
}

Floor *floor_create(f32 x, f32 y, f32 width) {
  Floor *floor = malloc(sizeof(Floor));
  floor_init(floor, x, y, width);
  return floor;
}

void floor_free(Floor *floor) {
  // Free the memory allocated for the floor object (ONLY IF IT WAS ALLOCATED by
  // malloc) otherwise, this function will cause a segmentation fault or other
  // issues.
  free(floor);
}

void player_free(Player *player) {
  // Free the memory allocated for the player object (ONLY IF IT WAS ALLOCATED
  // by malloc) otherwise, this function will cause a segmentation fault or
  // other issues.
  free(player);
}

void game_state_free(GameState *game) {
  // Free the memory allocated for the player object (ONLY IF IT WAS ALLOCATED
  // by malloc) otherwise, this function will cause a segmentation fault or
  // other issues.
  player_free(game->player);

  // Free the memory allocated for the floors array (ONLY IF IT WAS ALLOCATED by
  // malloc) otherwise, this function will cause a segmentation fault or other
  // issues.
  for (i32 i = 0; i < game->floor_count; i++) {
    floor_free(&game->floors[i]);
  }
}