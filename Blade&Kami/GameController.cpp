// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"
#include "CombatLogic.h"
#include "CombatSystem.h"

bool GameController::handleMainMenu(int choice) {
    switch (choice) {
    case 1: // Новая игра
        std::cin.ignore();
        state->currentMenu = MenuState::GAME_MENU;
        TextView::showMessage(u8"Новая игра начата!");
        return true;
    case 2: // Загрузить
        std::cin.ignore();
        TextView::showMessage(u8"Загрузка пока не реализована");
        return true;
    case 3: // Выход
        return false;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"Неверный выбор!");
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
        TextView::showMessage(u8"Сохранение пока не реализовано");
        return true;
    case 4: // Главное меню
        state->currentMenu = MenuState::MAIN_MENU;
        return true;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"Неверный выбор!");
        return true;
    }
}

bool GameController::handleMovement(int targetId) {
    // Ваша существующая логика перемещения
    for (auto& loc : state->locations) {
        if (loc.id == targetId) {
            for (int connId : state->currentLocation->connections) {
                if (connId == targetId) {
                    if (loc.enemyID != "") {
                        state->currentMenu = MenuState::COMBAT_MENU;
                    }
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
        state->currentMenu = MenuState::LEVEL_UP_MENU;
        break;
    case 2:
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
        TextView::showMessage(u8"Урон меча улучшен!");
        break;
    case 2:
        state->player.blade.upgradeStat(BladeStatType::ACCURACY);
        TextView::showMessage(u8"Точность повышена!");
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    }
}

CombatSystem::CombatResult GameController::handleCombatMenu(int choice, Enemy& enemy) {
    switch (choice) {
    case 1: // Атака
        return CombatSystem::updateCombat(state->player, enemy, choice);

    case 5: // Бежать
        // Возврат на предыдущую локацию
        for (auto& loc : state->locations) {
            if (loc.id == state->currentLocation->id - 1) {
                state->currentLocation = &loc;
                return CombatSystem::FLEE;
            }
        }
        return CombatSystem::FLEE;

    default:
        TextView::showMessage(u8"Неверный выбор!");
        return CombatSystem::IN_PROGRESS;
    }
}

void GameController::handleLevelUpMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::PLAYER_MENU;
        return;
    }

    if (state->player.availablePoints > 0) {
        state->player.increaseStat(choice);
        TextView::showMessage(u8"Характеристика улучшена!");
        std::cin.ignore();
    }
    else if (choice <=3) {
        TextView::showMessage(u8"Нет очков прокачки!");
        std::cin.ignore();
    }
    else {
        TextView::showMessage(u8"Некорректный ввод");
        std::cin.ignore();
    }
}