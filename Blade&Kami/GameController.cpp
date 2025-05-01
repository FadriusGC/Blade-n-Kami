// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"
#include "CombatLogic.h"
#include "CombatSystem.h"
#include "AbilityHandler.h"
#include "KuraiBlade.h"

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
    case 3:
        state->currentMenu = MenuState::INVENTORY_MENU;
        break;
    case 0:
        state->currentMenu = MenuState::GAME_MENU;
        break;
    }
}

void GameController::handleKuraiMenu(int choice) {
    switch (choice) {
    case 1:
        if (state->playerInventory.whetstones > 0) {
            state->player.blade.upgradeStat(BladeStatType::DAMAGE);
            state->playerInventory.whetstones--;
            TextView::showMessage(u8"���� ���� �������!");
            break;
        }
        else if (choice <= 2) {
            TextView::showMessage(u8"�� ������� ��������� ������.");
            break;
        }
        break;
    case 2:
        if (state->playerInventory.whetstones > 0) {
            state->player.blade.upgradeStat(BladeStatType::ACCURACY);
            state->playerInventory.whetstones--;
            TextView::showMessage(u8"�������� ��������!");
            break;
        }
        else if (choice <= 2) {
            TextView::showMessage(u8"�� ������� ��������� ������.");
            break;
        }
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"�������� �����!");
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

// GameController.cpp
void GameController::handleItemUse(int itemIndex) {
    auto& inv = state->playerInventory;
    if (itemIndex >= inv.items.size()) return;

    Item& item = inv.items[itemIndex];

    if (item.id == "sake_flask" && inv.sakeCharges > 0) {
        AbilityHandler::execute(item, state->player);
        inv.sakeCharges--;
    }
    /*else if (item.id == "whetstone" && inv.whetstones > 0) {
        state->player.blade.upgradeStat();
        inv.whetstones--;
    }*/
    else {
        AbilityHandler::execute(item, state->player);//, //currentEnemy);
        inv.items.erase(inv.items.begin() + itemIndex);
    }
}
void GameController::handleInventoryMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::PLAYER_MENU;
    }
    else {
        TextView::showMessage(u8"������������ ����");
        std::cin.ignore();
    }
}