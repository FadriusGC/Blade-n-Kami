#pragma once
#include "GameState.h"

class TextView {
public:
    static void showLocation(const Location& loc);
    static void showAvailableConnections(const GameState& state);
};