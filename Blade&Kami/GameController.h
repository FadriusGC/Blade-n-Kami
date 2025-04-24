#pragma once
#include "GameState.h"

class GameController {
    GameState* gameState;

public:
    GameController(GameState* gs) : gameState(gs) {}

    bool handleInput(char command) {
        switch (command) {
        case 'n': return moveTo(2); // Упрощенная логика
        case 's': return moveTo(1);
        default: return false;
        }
    }

private:
    bool moveTo(int targetId) {
        for (auto& loc : gameState->locations) {
            if (loc.id == targetId) {
                gameState->currentLocation = &loc;
                return true;
            }
        }
        return false;
    }
};
