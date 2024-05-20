#ifndef RAYLIB_GAME_H
#define RAYLIB_GAME_H

#include "../game/logic.h"
#include <raylib.h>

void run_game(GameState *game);
void input(bool *jump_pressed, bool *move_left, bool *move_right);
void render(const GameState *game);

#endif