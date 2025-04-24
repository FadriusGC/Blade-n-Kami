#pragma once
#include "GameState.h"

class GameController {
    GameState* state;
public:
    GameController(GameState* state) : state(state) {}
    bool handleInput(int targetId);
};