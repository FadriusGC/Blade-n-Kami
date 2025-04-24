// GameController.cpp
#include "GameController.h"
#include "TextView.h"

bool GameController::handleMainMenu(int choice) {
    switch (choice) {
    case 1: // Новая игра
        std::cin.ignore();
        state->currentMenu = MenuState::GAME_MENU;
        TextView::showMessage("Новая игра начата!");
        return true;
    case 2: // Загрузить
        std::cin.ignore();
        TextView::showMessage("Загрузка пока не реализована");
        return true;
    case 3: // Выход
        return false;
    default:
        std::cin.ignore();
        TextView::showMessage("Неверный выбор!");
        return true;
    }
}

bool GameController::handleGameMenu(int choice) {
    switch (choice) {
    case 1: // Передвижение
        state->currentMenu = MenuState::MOVE_MENU;
        return true;
    case 2: // Статы
        std::cin.ignore();
        TextView::showMessage("Статистика игрока пока не реализована");
        return true;
    case 3: // Сохранить
        std::cin.ignore();
        TextView::showMessage("Сохранение пока не реализовано");
        return true;
    case 4: // Главное меню
        state->currentMenu = MenuState::MAIN_MENU;
        return true;
    default:
        std::cin.ignore();
        TextView::showMessage("Неверный выбор!");
        return true;
    }
}

bool GameController::handleMovement(int targetId) {
    // Ваша существующая логика перемещения
    for (auto& loc : state->locations) {
        if (loc.id == targetId) {
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