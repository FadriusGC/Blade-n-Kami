#include "GameController.h"

bool GameController::handleInput(int targetId) {
    for (auto& loc : state->locations) {
        if (loc.id == targetId) {
            // ���������, ���� �� �����
            for (int connId : state->currentLocation->connections) {
                if (connId == targetId) {
                    state->currentLocation = &loc;
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}