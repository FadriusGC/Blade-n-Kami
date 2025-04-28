// GameController.h
#pragma once
#include "GameState.h"
#include "CombatSystem.h"

class GameController {
    GameState* state;

public:
    explicit GameController(GameState* state) : state(state) {}

    bool handleMainMenu(int choice);
    bool handleGameMenu(int choice);
    bool handleMovement(int targetId);
    void handlePlayerMenu(int choice);
    void handleLevelUpMenu(int choice);
    void handleKuraiMenu(int choice);
    CombatSystem::CombatResult handleCombatMenu(int choice, Enemy& enemy);
};