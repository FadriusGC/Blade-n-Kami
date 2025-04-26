// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"

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
        state->currentMenu = MenuState::PLAYER_MENU;
        return true;
    case 3: // Сохранить
        std::cin.ignore();
       /* TextView::showMessage("Сохранение пока не реализовано");*/
        TextView::showEnemyInfo; 
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

void GameController::handlePlayerMenu(int choice) {
    switch (choice) {
    case 1:
        state->player.strength += 2;
        TextView::showMessage("Сила увеличена!");
        break;
    case 2:
        state->player.spirit += 2;
        TextView::showMessage("Дух усилен!");
        break;
    case 3:
        state->currentMenu = MenuState::KURAI_MENU;
        break;
    case 0:
        state->currentMenu = MenuState::GAME_MENU;
        break;
    }
}

void GameController::handleKuraiMenu(int choice) {
    switch (choice) {
    case 1:
        state->player.blade.upgradeStat(BladeStatType::DAMAGE);
        TextView::showMessage("Урон меча улучшен!");
        break;
    case 2:
        state->player.blade.upgradeStat(BladeStatType::ACCURACY);
        TextView::showMessage("Точность повышена!");
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    }
}