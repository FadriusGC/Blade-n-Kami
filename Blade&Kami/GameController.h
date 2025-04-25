// GameController.h
#pragma once
#include "GameState.h"

class GameController {
    GameState* state;

public:
    explicit GameController(GameState* state) : state(state) {}

    bool handleMainMenu(int choice);
    bool handleGameMenu(int choice);
    bool handleMovement(int targetId);
    void handlePlayerMenu(int choice);
    void handleKuraiMenu(int choice);
};