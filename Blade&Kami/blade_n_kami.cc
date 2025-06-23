#include <Windows.h>

#include <iostream>
#include <sstream>

#include "ability_handler.h"
#include "combat_system.h"
#include "enemy_factory.h"
#include "game_controller.h"
#include "game_state.h"
#include "input_handler.h"
#include "inventory.h"
#include "item_factory.h"
#include "localisation.h"
#include "text_view.h"

int main() {
  Localise();
  try {
    GameState state;
    state.Initialize("locations.txt", "enemies.txt", "items.txt",
                     "blessings.txt");
    AbilityHandler::InitAbilities();
    BlessingSystem::InitBlessings();
    GameController controller(&state);
    Player player;
    std::string input;
    bool isRunning = true;

    TextView::ShowMessage(u8"Тест загрузки врагов:");
    TextView::ShowEnemyList(state.enemy_templates_);

    state.player_inventory_.AddItem("health_potion", state);
    state.player_inventory_.AddItem("bomb", state);
    state.player_inventory_.AddItem("health_potion", state);

    // Создайте тестового врага
    Enemy testEnemy = EnemyFactory::CreateEnemy(state, "wolf");
    TextView::ShowEnemyDetails(testEnemy);
    Enemy testEnemy2 = EnemyFactory::CreateEnemy(state, "goblin");
    TextView::ShowEnemyDetails(testEnemy2);
    // state.player.changeKi(-34);

    while (isRunning) {
      std::cin.ignore();
      TextView::ClearScreen();
      switch (state.current_menu_) {
        case MenuState::kMainMenu: {
          TextView::ShowMainMenu();
          isRunning = controller.HandleMainMenu(InputHandler::GetInput());
          break;
        }

        case MenuState::kGameMenu: {
          TextView::ShowGameMenu();
          controller.HandleGameMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kLocationMenu: {
          TextView::ShowLocationMenu(*state.current_location_);
          controller.HandleLocationMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kMoveMenu: {
          TextView::ShowLocation(*state.current_location_);
          TextView::ShowAvailableConnections(state);
          controller.HandleMovement(InputHandler::GetInput());
          break;
        }

        case MenuState::kPlayerMenu: {
          TextView::ShowPlayerMenu(state.player_);
          controller.HandlePlayerMenu(InputHandler::GetInput());
          break;
        }

        case MenuState::kKuraiMenu: {
          TextView::ShowKuraiMenu(state.player_.blade_);
          controller.HandleKuraiMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kCombatMenu: {
          CombatSystem::InitializeCombat(state);
          TextView::ShowCombatStats(state.player_, *state.current_enemy_);
          TextView::ShowCombatMenu(state.player_, *state.current_enemy_);
          auto result = controller.HandleCombatMenu(InputHandler::GetInput(),
                                                    *state.current_enemy_);
          CombatSystem::HandleCombatResult(result, state);
          break;
        }

        case MenuState::kLevelUpMenu: {
          TextView::ShowLevelUpMenu(state.player_);
          controller.HandleLevelUpMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kInventoryMenu: {
          TextView::ShowInventory(state.player_inventory_);
          controller.HandleInventoryMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kInvCombatMenu: {
          TextView::ShowInventoryCombat(state.player_inventory_);
          controller.HandleInventoryCombatMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kAltarMenu: {
          // Проверка на доступные благословения
          if (state.current_altar_blessings_.empty()) {
            TextView::ShowMessage(u8"Нет доступных благословений!");
            std::cin.ignore();
            state.current_menu_ = MenuState::kLocationMenu;
            break;
          }

          TextView::ShowAltarMenu(state.current_altar_blessings_,
                                  state.player_);

          controller.HandleAltarMenu(InputHandler::GetInput());

          break;
        }
        case MenuState::kBlessingMenu: {
          TextView::ShowBlessingMenu(state.player_.blessings_, state.player_);
          controller.HandleBlessingMenu(InputHandler::GetInput());
          break;
        }
        case MenuState::kBlessingCombatMenu: {
          std::vector<Blessing> activeBlessings;
          for (const auto& blessing : state.player_.blessings_) {
            if (blessing.type == BlessingType::kActive) {
              activeBlessings.push_back(blessing);
            }
          }

          TextView::ShowCombatBlessingsMenu(activeBlessings, state.player_);
          controller.HandleBlessingCombatMenu(InputHandler::GetInput());
          break;
        }
      }
    }
  } catch (const std::exception& e) {
    std::cerr << u8"Ошибка: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
