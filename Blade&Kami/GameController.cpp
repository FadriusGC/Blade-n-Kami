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
        return true;   //� ����� ������� ����� ����������, ������ ������� ��� std::cin.ignore() �.�. ����������� ������ ������ getInput � ����������� �� ���� ������ ���.
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
    if (targetId == 0) {
        state->currentMenu = MenuState::GAME_MENU;
        return true;
    }

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
            std::cin.ignore();
            TextView::showMessage(u8"������������ ����� �������!");
            return false;
		}
    }
    std::cin.get();
    //std::cin.ignore();
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
    default:
        std::cin.ignore();
        TextView::showMessage(u8"�������� �����!");
        break;
    }
}

void GameController::handleKuraiMenu(int choice) {
    switch (choice) {
    case 1:
        if (state->playerInventory.whetstones > 0) {
            state->player.blade.upgradeStat(BladeStatType::DAMAGE);
            state->playerInventory.whetstones--;
            std::cin.ignore();
            TextView::showMessage(u8"���� ���� �������!");
            break;
        }
        else if (choice <= 2) {
            std::cin.ignore();
            TextView::showMessage(u8"�� ������� ��������� ������.");
            break;
        }
        break;
    case 2:
        if (state->playerInventory.whetstones > 0) {
            state->player.blade.upgradeStat(BladeStatType::ACCURACY);
            state->playerInventory.whetstones--;
            std::cin.ignore();
            TextView::showMessage(u8"�������� ��������!");
            break;
        }
        else if (choice <= 2) {
            std::cin.ignore();
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
    case 1:  // �����
        CombatSystem::updateCombat(state->player, enemy, choice, *state);
        break;
	case 2:// ��������
		CombatSystem::updateCombat(state->player, enemy, choice, *state);
		break;
    case 3: // ��������
        state->currentMenu = MenuState::INV_COMBAT_MENU;
        return CombatSystem::IN_PROGRESS;
        break;
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
        std::cin.ignore();
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
		if (choice < 1 || choice > 3) {
			TextView::showMessage(u8"������������ ����� ��������������!");
			std::cin.ignore();
			return;
		}
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

void GameController::handleInventoryMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::PLAYER_MENU;
    }
    else {
        TextView::showMessage(u8"������������ ����");
        std::cin.ignore();
    }
}

void GameController::handleInventoryCombatMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::COMBAT_MENU;
        return;
    }

    try {
        int itemIndex = choice - 1;
        this->handleItemUse(itemIndex);
    }
    catch (...) {
        TextView::showMessage(u8"������ ������������� ��������!");
    }
}

void GameController::handleItemUse(int itemIndex) {
    auto& inv = state->playerInventory;
    if (itemIndex < 0 || itemIndex >= inv.items.size()) {
        std::cin.ignore();
        TextView::showMessage(u8"������ �������� � ��� ���!");
        return;
	}

    Item& item = inv.items[itemIndex];

    try {
        TextView::showMessage(u8"����������� �������: [" + item.name + u8"]" + u8"!");
        // ��� ������������, ��������� �����
        AbilityHandler::execute(item, state->player, state->currentEnemy);
        std::cin.ignore();
        // �������� ����������� ���������
        if (item.id != "sake_flask") {
            inv.items.erase(inv.items.begin() + itemIndex);
        }
    }
    catch (const std::exception& e) {
        TextView::showMessage(e.what());
    }
}