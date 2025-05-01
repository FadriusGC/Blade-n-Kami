// Inventory.h
#pragma once
#include <vector>
#include <string>
#include "Item.h"
#include "ItemFactory.h"
#include "GameState.h"
#include <iostream>

class Inventory {
public:
    std::vector<Item> items;
    int sakeCharges = 2;  // Заряды Фляги Сакэ
    int whetstones = 0;   // Количество Точильных Камней

    // Добавление предмета по ID через фабрику
    void addItem(const std::string& itemId, const GameState& state) {
        try {
            Item newItem = ItemFactory::createItem(state, itemId);

            // Обработка специальных предметов
            if (newItem.id == "sake_flask") {
                sakeCharges++;
            }
            else if (newItem.id == "whetstone") {
                whetstones++;
            }
            else {
                items.push_back(newItem);
            }

        }
        catch (const std::exception& e) {
            // Логирование ошибки (можно заменить на вывод в UI)
            std::cerr << u8"[ОШИБКА] Не удалось добавить предмет: " << e.what() << std::endl;
        }
    }

    // Удаление предмета по ID
    void removeItem(const std::string& itemId) {
        items.erase(
            std::remove_if(items.begin(), items.end(),
                [&itemId](const Item& item) { return item.id == itemId; }),
            items.end()
        );
    }
};