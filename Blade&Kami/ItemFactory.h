// ItemFactory.h
#pragma once
#include <stdexcept>
#include <string>
#include "Item.h"
// ��������������� ����������
class GameState;

class ItemFactory {
public:
    static Item createItem(const GameState& state, const std::string& itemId);
};