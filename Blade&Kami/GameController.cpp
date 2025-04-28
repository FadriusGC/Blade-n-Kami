// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"
#include "CombatLogic.h"
#include "CombatSystem.h"

bool GameController::handleMainMenu(int choice) {
    switch (choice) {
    case 1: // ����� ����
        std::cin.ignore();
        state->currentMenu = MenuState::GAME_MENU;
        TextView::showMessage(u8"����� ���� ������!");
        return true;
    case 2: // ���������
        std::cin.ignore();
        TextView::showMessage(u8"�������� ���� �� �����������");
        return true;
    case 3: // �����
        return false;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"�������� �����!");
        return true;
    }
}

bool GameController::handleGameMenu(int choice) {
    switch (choice) {
    case 1: // ������������
        state->currentMenu = MenuState::MOVE_MENU;
        return true;
    case 2: // �����
        state->currentMenu = MenuState::PLAYER_MENU;
        return true;
    case 3: // ���������
        std::cin.ignore();
        TextView::showMessage(u8"���������� ���� �� �����������");
        return true;
    case 4: // ������� ����
        state->currentMenu = MenuState::MAIN_MENU;
        return true;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"�������� �����!");
        return true;
    }
}

bool GameController::handleMovement(int targetId) {
    // ���� ������������ ������ �����������
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
        TextView::showMessage(u8"���� ���� �������!");
        break;
    case 2:
        state->player.blade.upgradeStat(BladeStatType::ACCURACY);
        TextView::showMessage(u8"�������� ��������!");
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    }
}

CombatSystem::CombatResult GameController::handleCombatMenu(int choice, Enemy& enemy) {
    switch (choice) {
    case 1: // �����
        return CombatSystem::updateCombat(state->player, enemy, choice);

    case 5: // ������
        // ������� �� ���������� �������
        for (auto& loc : state->locations) {
            if (loc.id == state->currentLocation->id - 1) {
                state->currentLocation = &loc;
                return CombatSystem::FLEE;
            }
        }
        return CombatSystem::FLEE;

    default:
        TextView::showMessage(u8"�������� �����!");
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
        TextView::showMessage(u8"�������������� ��������!");
        std::cin.ignore();
    }
    else if (choice <=3) {
        TextView::showMessage(u8"��� ����� ��������!");
        std::cin.ignore();
    }
    else {
        TextView::showMessage(u8"������������ ����");
        std::cin.ignore();
    }
}