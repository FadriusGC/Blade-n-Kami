#pragma once
#include "Location.h"
#include <vector>

class GameState {
public:
    std::vector<Location> locations;
    Location* currentLocation;

    void initializeLocations() {
        // Создаем 3 тестовые комнаты
        locations.emplace_back(1, "Опушка Заката", "Закатные лучи пробиваются сквозь листву.");
        locations.emplace_back(2, "Тропа Папоротников", "Гигантские папоротники шелестят на ветру.");
        locations.emplace_back(3, "Ручей Хрустальной Воды", "Вода чиста, но под ней скрывается опасность.");

        // Связываем комнаты
        locations[0].connectedLocations = { 2 };    // Опушка → Тропа
        locations[1].connectedLocations = { 1,3 };  // Тропа → Опушка и Ручей
        locations[2].connectedLocations = { 2 };    // Ручей → Тропа

        currentLocation = &locations[0]; // Стартовая локация
    }
};