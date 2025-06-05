#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include "EnemyFactory.h"
#include "Localisation.h"
#include "CombatSystem.h"
#include "AbilityHandler.h"
#include "Inventory.h"
#include "ItemFactory.h"
#include "InputHandler.h"

int main() {
    localise();
    try {
        GameState state;
        state.initialize("locations.txt", "enemies.txt", "items.txt");
        AbilityHandler::initAbilities();
        GameController controller(&state);
        Player player;
        std::string input;
        bool isRunning = true;

        TextView::showMessage(u8"Тест загрузки врагов:");
        TextView::showEnemyList(state.enemyTemplates);

        state.playerInventory.addItem("health_potion", state);
        state.playerInventory.addItem("bomb", state);
        state.playerInventory.addItem("health_potion", state);

        // Создайте тестового врага
        Enemy testEnemy = EnemyFactory::createEnemy(state, "wolf");
        TextView::showEnemyDetails(testEnemy);
        Enemy testEnemy2 = EnemyFactory::createEnemy(state, "goblin");
        TextView::showEnemyDetails(testEnemy2);
        //state.player.changeKi(-34);

        while (isRunning) {
            std::cin.ignore();
            TextView::clearScreen();
            switch (state.currentMenu) {
            case MenuState::MAIN_MENU: {
                TextView::showMainMenu();
                isRunning = controller.handleMainMenu(InputHandler::getInput());
                break;
            }

            case MenuState::GAME_MENU: {
                TextView::showGameMenu();
                controller.handleGameMenu(InputHandler::getInput());
                break;
            }

            case MenuState::MOVE_MENU: {
                TextView::showLocation(*state.currentLocation);
                TextView::showAvailableConnections(state);
                controller.handleMovement(InputHandler::getInput());
                break;
            }

            case MenuState::PLAYER_MENU: {
                TextView::showPlayerMenu(state.player);
                controller.handlePlayerMenu(InputHandler::getInput());
                break;
            }

            case MenuState::KURAI_MENU: {
                TextView::showKuraiMenu(state.player.blade);
                controller.handleKuraiMenu(InputHandler::getInput());
                break;
            }
            case MenuState::COMBAT_MENU: {
                // Инициализация боя при входе
                if (!state.currentEnemy && state.currentLocation->enemyID != "") {
                    state.newEnemy = new Enemy(EnemyFactory::createEnemy(state, state.currentLocation->enemyID));
                    state.currentEnemy = state.newEnemy; 
                } 

                // Отображение интерфейса
                TextView::showCombatStats(state.player, *state.currentEnemy);
                TextView::showCombatMenu(state.player, *state.currentEnemy);

                auto result = controller.handleCombatMenu(InputHandler::getInput(), *state.currentEnemy);

                // Обработка результатов
                switch (result) {
                case CombatSystem::PLAYER_WIN:
                    state.currentEnemy = nullptr;
                    delete state.newEnemy;
                    state.currentLocation->enemyID = "";
                    std::cin.ignore();
                    state.currentMenu = MenuState::GAME_MENU;
                    break;

                case CombatSystem::ENEMY_WIN:
                    TextView::showMessage(u8"Игрок погиб, игра окончена :(");
                    std::cin.ignore();
                    exit(0);

                case CombatSystem::FLEE:
                    state.currentMenu = MenuState::GAME_MENU;
                    state.currentEnemy = nullptr;
                    delete state.newEnemy;    
                    break;
                }
                break;
            }
            
            case MenuState::LEVEL_UP_MENU: {
                TextView::showLevelUpMenu(state.player);
                controller.handleLevelUpMenu(InputHandler::getInput());
                break;
            }
            case MenuState::INVENTORY_MENU: {
                TextView::showInventory(state.playerInventory);
                controller.handleInventoryMenu(InputHandler::getInput());
                break;
            }
            case MenuState::INV_COMBAT_MENU: {
                TextView::showInventoryCombat(state.playerInventory);
                controller.handleInventoryCombatMenu(InputHandler::getInput());
                break;
            }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << u8"Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
