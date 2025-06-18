// GameController.cpp
#include "GameController.h"
#include "TextView.h"
#include "EnemyFactory.h"
#include "CombatLogic.h"
#include "CombatSystem.h"
#include "AbilityHandler.h"
#include "KuraiBlade.h"
#include "InputHandler.h"
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
        return true;   //в целом дефолты можно переписать, просто оставив там std::cin.ignore() т.к. отображение ошибок делает getInput и дублировать по сути смысла нет.
    }
}

bool GameController::handleGameMenu(int choice) {
    switch (choice) {
    case 1: // Передвижение
        state->currentMenu = MenuState::LOCATION_MENU;
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
void GameController::handleLocationMenu(int choice) {
    switch (choice) {
    case 1: // Перемещение
        state->currentMenu = MenuState::MOVE_MENU;
        break;
    case 2: // Осмотреться
        handleLocationExplore();
        break;
    case 0: // Назад
        state->currentMenu = MenuState::GAME_MENU;
        break;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"Неверный выбор!");
        break;
    }
}
void GameController::handleLocationExplore() {
    TextView::showLocationDetails(*state->currentLocation);
    std::cin.ignore();

    // Проверяем наличие объекта
    if (!state->currentLocation->objectID.empty() && !state->currentLocation->objectUsed) {
        if (state->currentLocation->objectID == "chest") {
            int goldFound = 10 + state->player.level * 10;
            state->player.gainGold(goldFound);

            // Помечаем сундук как использованный
            state->currentLocation->objectUsed = true;

            TextView::showChestInteraction(goldFound);
            //std::cin.ignore();
        }
        else if (state->currentLocation->objectID == "altar") {
            // Алтарь Ками
            state->currentAltarBlessings = BlessingSystem::getRandomBlessings(
                state->blessingTemplates,
                state->player.blessings,
                3);
            TextView::showMessage(u8"🏛️ Вы обнаружили древний Алтарь Ками!");
            std::cin.ignore();
            state->currentMenu = MenuState::ALTAR_MENU;
            return;
        }
    }
}
bool GameController::handleMovement(int targetId) {
    if (targetId == 0) {
        state->currentMenu = MenuState::LOCATION_MENU;
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
                    //state->currentMenu = MenuState::LOCATION_MENU;
                    return true;
                }
            }
            std::cin.ignore();
            TextView::showMessage(u8"Неправильный выбор локации!");
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
        TextView::showMessage(u8"Неверный выбор!");
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
            TextView::showMessage(u8"Урон меча улучшен!");
            break;
        }
        else if (choice <= 2) {
            std::cin.ignore();
            TextView::showMessage(u8"Не хватает точильных камней.");
            break;
        }
        break;
    case 2:
        if (state->playerInventory.whetstones > 0) {
            state->player.blade.upgradeStat(BladeStatType::ACCURACY);
            state->playerInventory.whetstones--;
            std::cin.ignore();
            TextView::showMessage(u8"Точность повышена!");
            break;
        }
        else if (choice <= 2) {
            std::cin.ignore();
            TextView::showMessage(u8"Не хватает точильных камней.");
            break;
        }
        break;
    case 0:
        state->currentMenu = MenuState::PLAYER_MENU;
        break;
    default:
        std::cin.ignore();
        TextView::showMessage(u8"Неверный выбор!");
        break;
    }
 }

CombatSystem::CombatResult GameController::handleCombatMenu(int choice, Enemy& enemy) {
    switch (choice) {
    case 1:  // Атака
        CombatSystem::updateCombat(state->player, enemy, choice, *state);
        break;
	case 2:// Очищение
		CombatSystem::updateCombat(state->player, enemy, choice, *state);
		break;
    case 3: // Предметы
        state->currentMenu = MenuState::INV_COMBAT_MENU;
        return CombatSystem::IN_PROGRESS;
        break;
    case 4:  // Благословения (новый пункт)
        state->currentMenu = MenuState::BLESSING_COMBAT_MENU;
        return CombatSystem::IN_PROGRESS;
        break;
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
        std::cin.ignore();
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
		if (choice < 1 || choice > 3) {
			TextView::showMessage(u8"Некорректный выбор характеристики!");
			std::cin.ignore();
			return;
		}
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

void GameController::handleInventoryMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::PLAYER_MENU;
    }
    else {
        TextView::showMessage(u8"Некорректный ввод");
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
        TextView::showMessage(u8"Ошибка использования предмета!");
    }
}

void GameController::handleItemUse(int itemIndex) {
    auto& inv = state->playerInventory;
    if (itemIndex < 0 || itemIndex >= inv.items.size()) {
        std::cin.ignore();
        TextView::showMessage(u8"Такого предмета у вас нет!");
        return;
	}

    Item& item = inv.items[itemIndex];

    try {
        TextView::showMessage(u8"Использован предмет: [" + item.name + u8"]" + u8"!");
        // Для способностей, требующих врага
        AbilityHandler::execute(item, state->player, state->currentEnemy);
        std::cin.ignore();
        // Удаление расходуемых предметов
        if (item.id != "sake_flask") {
            inv.items.erase(inv.items.begin() + itemIndex);
        }
    }
    catch (const std::exception& e) {
        TextView::showMessage(e.what());
    }
}

void GameController::handleAltarMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::LOCATION_MENU;
        return;
    }

    // Получаем случайные благословения
    auto& availableBlessings = state->currentAltarBlessings;

    if (availableBlessings.empty()) {
        TextView::showMessage(u8"У вас уже есть все доступные благословения!");
        std::cin.ignore();
        state->currentMenu = MenuState::LOCATION_MENU;
        return;
    }

    if (choice > 0 && choice <= availableBlessings.size()) {
        Blessing selectedBlessing = availableBlessings[choice - 1];

        // Показываем детали благословения
        TextView::showBlessingDetails(selectedBlessing, state->player);
        std::cin.ignore();

        // Подтверждение выбора
        TextView::showMessage(u8"Получить это благословение? (1 - Да, 0 - Нет): ");
        int confirm = InputHandler::getInput();

        if (confirm == 1) {
            state->player.addBlessing(selectedBlessing);
            TextView::showMessage(u8"✨ Вы получили благословение: " + selectedBlessing.name);

            // Применяем пассивные эффекты
            BlessingSystem::applyPassiveBlessings(state->player, { selectedBlessing });

            // Помечаем алтарь как использованный
            state->currentLocation->objectUsed = true;

            std::cin.ignore();
            state->currentMenu = MenuState::LOCATION_MENU;
        }
        else {
            state->currentMenu = MenuState::ALTAR_MENU;
        }
    }
    else {
        TextView::showMessage(u8"Некорректный выбор!");
        std::cin.ignore();
    }
}

void GameController::handleBlessingCombatMenu(int choice) {
    if (choice == 0) {
        state->currentMenu = MenuState::COMBAT_MENU;
        return;
    }

    // Получаем только активные благословения
    std::vector<Blessing> activeBlessings;
    for (const auto& blessing : state->player.blessings) {
        if (blessing.type == BlessingType::ACTIVE) {
            activeBlessings.push_back(blessing);
        }
    }

    if (choice > 0 && choice <= activeBlessings.size()) {
        Blessing& selectedBlessing = activeBlessings[choice - 1];

        if (BlessingSystem::canUseBlessing(selectedBlessing, state->player)) {
            BlessingSystem::executeBlessing(selectedBlessing, state->player, state->currentEnemy);
            std::cin.ignore();
            state->currentMenu = MenuState::COMBAT_MENU;
        }
        else {
            TextView::showMessage(u8"🌀 Недостаточно Рэйки для использования благословения!");
            std::cin.ignore();
        }
    }
    else {
        TextView::showMessage(u8"Некорректный выбор!");
        std::cin.ignore();
    }
}

void GameController::handleBlessingMenu(int choice) {

}
