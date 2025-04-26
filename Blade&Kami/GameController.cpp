// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"

bool GameController::handleMainMenu(int choice) {
    switch (choice) {
    case 1: // ����� ����
        std::cin.ignore();
        state->currentMenu = MenuState::GAME_MENU;
        TextView::showMessage("����� ���� ������!");
        return true;
    case 2: // ���������
        std::cin.ignore();
        TextView::showMessage("�������� ���� �� �����������");
        return true;
    case 3: // �����
        return false;
    default:
        std::cin.ignore();
        TextView::showMessage("�������� �����!");
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
       /* TextView::showMessage("���������� ���� �� �����������");*/
        TextView::showEnemyInfo; 
        return true;
    case 4: // ������� ����
        state->currentMenu = MenuState::MAIN_MENU;
        return true;
    default:
        std::cin.ignore();
        TextView::showMessage("�������� �����!");
        return true;
    }
}

bool GameController::handleMovement(int targetId) {
    // ���� ������������ ������ �����������
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
        TextView::showMessage("���� ���������!");
        break;
    case 2:
        state->player.spirit += 2;
        TextView::showMessage("��� ������!");
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
        TextView::showMessage("���� ���� �������!");
        break;
    case 2:
        state->player.blade.upgradeStat(BladeStatType::ACCURACY);
        TextView::showMessage("�������� ��������!");
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    }
}