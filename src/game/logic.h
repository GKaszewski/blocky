#ifndef LOGIC_H
#define LOGIC_H

#include "data.h"

void init_game(GameState *game);
void update_game(GameState *game, f32 dt, bool jump_pressed, bool move_left,
                 bool move_right);

typedef void (*RenderFunction)(const GameState *game);
typedef void (*InputFunction)(bool *jump_pressed, bool *move_left,
                              bool *move_right);

void game_loop(GameState *game, RenderFunction render, InputFunction input,
               f32 dt);

#endif