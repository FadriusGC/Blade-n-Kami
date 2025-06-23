#include "game_controller.h"

#include <filesystem>

#include "ability_handler.h"
#include "combat_logic.h"
#include "combat_system.h"
#include "enemy_factory.h"
#include "input_handler.h"
#include "kurai_blade.h"
#include "text_view.h"
bool GameController::HandleMainMenu(int choice) {
  switch (choice) {
    case 1:
      std::cin.ignore();
      state_->current_menu_ = MenuState::kGameMenu;
      TextView::ShowMessage(u8"Новая игра начата!");
      return true;
    case 2:
      try {
        if (!std::filesystem::exists("save.txt")) {
          TextView::ShowMessage(u8"Ошибка: Файл сохранения не найден!");
          std::cin.ignore();
          return true;
        }
        state_->LoadFromFile("save.txt");
        state_->current_menu_ = MenuState::kGameMenu;
        TextView::ShowMessage(u8"Игра загружена!");
        std::cin.ignore();
      } catch (const std::exception& e) {
        TextView::ShowMessage(u8"Ошибка загрузки: " + std::string(e.what()));
      }
      return true;
    case 3:
      return false;
    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      return true;  // в целом дефолты можно переписать, просто оставив там
                    // std::cin.ignore() т.к. отображение ошибок делает getInput
                    // и дублировать по сути смысла нет.
  }
}

bool GameController::HandleGameMenu(int choice) {
  switch (choice) {
    case 1:
      state_->current_menu_ = MenuState::kLocationMenu;
      return true;
    case 2:
      state_->current_menu_ = MenuState::kPlayerMenu;
      return true;
    case 3:
      try {
        state_->SaveToFile("save.txt");
        TextView::ShowMessage(u8"Игра сохранена!");
        std::cin.ignore();
      } catch (const std::exception& e) {
        TextView::ShowMessage(u8"Ошибка сохранения: " + std::string(e.what()));
      }
      return true;
    case 4:
      state_->current_menu_ = MenuState::kMainMenu;
      return true;
    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      return true;
  }
}
void GameController::HandleLocationMenu(int choice) {
  switch (choice) {
    case 1:
      state_->current_menu_ = MenuState::kMoveMenu;
      break;
    case 2:
      HandleLocationExplore();
      break;
    case 0:
      state_->current_menu_ = MenuState::kGameMenu;
      break;
    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      break;
  }
}
void GameController::HandleLocationExplore() {
  TextView::ShowLocationDetails(*state_->current_location_);
  std::cin.ignore();

  // Проверяем наличие объекта
  if (!state_->current_location_->object_id_.empty() &&
      !state_->current_location_->object_used_) {
    if (state_->current_location_->object_id_ == "chest") {
      int gold_found = 10 + state_->player_.level_ * 10;
      state_->player_.GainGold(gold_found);

      state_->current_location_->object_used_ = true;

      TextView::ShowChestInteraction(gold_found);
    } else if (state_->current_location_->object_id_ == "altar") {
      // Алтарь Ками
      if (state_->current_altar_blessings_.empty()) {
        state_->current_altar_blessings_ = BlessingSystem::GetRandomBlessings(
            state_->blessing_templates_, state_->player_.blessings_, 3);
      }
      TextView::ShowMessage(u8"🏛️ Вы обнаружили древний Алтарь Ками!");
      state_->current_menu_ = MenuState::kAltarMenu;
      return;
    }
  }
}
bool GameController::HandleMovement(int targetId) {
  if (targetId == 0) {
    state_->current_menu_ = MenuState::kLocationMenu;
    return true;
  }

  for (auto& loc : state_->locations_) {
    if (loc.id_ == targetId) {
      for (int conn_id : state_->current_location_->connections_) {
        if (conn_id == targetId) {
          if (loc.enemy_id_ != "") {
            state_->current_menu_ = MenuState::kCombatMenu;
          }
          state_->current_location_ = &loc;
          // state->currentMenu = MenuState::LOCATION_MENU;
          return true;
        }
      }
      std::cin.ignore();
      TextView::ShowMessage(u8"Неправильный выбор локации!");
      return false;
    }
  }
  std::cin.get();
  return false;
}

void GameController::HandlePlayerMenu(int choice) {
  switch (choice) {
    case 1:
      state_->current_menu_ = MenuState::kLevelUpMenu;
      break;
    case 2:
      state_->current_menu_ = MenuState::kKuraiMenu;
      break;
    case 3:
      state_->current_menu_ = MenuState::kInventoryMenu;
      break;
    case 4:
      state_->current_menu_ = MenuState::kBlessingMenu;
      break;
    case 0:
      state_->current_menu_ = MenuState::kGameMenu;
      break;
    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      break;
  }
}

void GameController::HandleKuraiMenu(int choice) {
  switch (choice) {
    case 1:
      if (state_->player_inventory_.whetstones_ > 0) {
        state_->player_.blade_.upgradeStat(BladeStatType::kDamage);
        state_->player_inventory_.whetstones_--;
        std::cin.ignore();
        TextView::ShowMessage(u8"Урон меча улучшен!");
        break;
      } else if (choice <= 2) {
        std::cin.ignore();
        TextView::ShowMessage(u8"Не хватает точильных камней.");
        break;
      }
      break;
    case 2:
      if (state_->player_inventory_.whetstones_ > 0) {
        state_->player_.blade_.upgradeStat(BladeStatType::kAccuracy);
        state_->player_inventory_.whetstones_--;
        std::cin.ignore();
        TextView::ShowMessage(u8"Точность повышена!");
        break;
      } else if (choice <= 2) {
        std::cin.ignore();
        TextView::ShowMessage(u8"Не хватает точильных камней.");
        break;
      }
      break;
    case 0:
      state_->current_menu_ = MenuState::kPlayerMenu;
      break;
    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      break;
  }
}

CombatSystem::CombatResult GameController::HandleCombatMenu(int choice,
                                                            Enemy& enemy) {
  switch (choice) {
    case 1:  // Атака
      CombatSystem::UpdateCombat(state_->player_, enemy, choice, *state_);
      break;
    case 2:  // Очищение
      CombatSystem::UpdateCombat(state_->player_, enemy, choice, *state_);
      break;
    case 3:  // Предметы
      state_->current_menu_ = MenuState::kInvCombatMenu;
      return CombatSystem::kInProgress;
      break;
    case 4:  // Благословения (новый пункт)
      state_->current_menu_ = MenuState::kBlessingCombatMenu;
      return CombatSystem::kInProgress;
      break;
    case 5:  // Бежать
      // Возврат на предыдущую локацию
      for (auto& loc : state_->locations_) {
        if (loc.id_ == state_->current_location_->id_ - 1) {
          state_->current_location_ = &loc;
          return CombatSystem::kFlee;
        }
      }
      return CombatSystem::kFlee;

    default:
      std::cin.ignore();
      TextView::ShowMessage(u8"Неверный выбор!");
      return CombatSystem::kInProgress;
  }
}

void GameController::HandleLevelUpMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kPlayerMenu;
    return;
  }
  if (state_->player_.available_points_ > 0) {
    if (choice < 1 || choice > 3) {
      TextView::ShowMessage(u8"Некорректный выбор характеристики!");
      std::cin.ignore();
      return;
    }
    state_->player_.IncreaseStat(choice);
    TextView::ShowMessage(u8"Характеристика улучшена!");
    std::cin.ignore();
  } else if (choice <= 3) {
    TextView::ShowMessage(u8"Нет очков прокачки!");
    std::cin.ignore();
  } else {
    TextView::ShowMessage(u8"Некорректный ввод");
    std::cin.ignore();
  }
}

void GameController::HandleInventoryMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kPlayerMenu;
  } else {
    TextView::ShowMessage(u8"Некорректный ввод");
    std::cin.ignore();
  }
}

void GameController::HandleInventoryCombatMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kCombatMenu;
    return;
  }

  try {
    int item_index = choice - 1;
    this->HandleItemUse(item_index);
  } catch (...) {
    TextView::ShowMessage(u8"Ошибка использования предмета!");
  }
}

void GameController::HandleItemUse(int item_index) {
  auto& inv = state_->player_inventory_;
  if (item_index < 0 || item_index >= inv.items_.size()) {
    std::cin.ignore();
    TextView::ShowMessage(u8"Такого предмета у вас нет!");
    return;
  }

  Item& item = inv.items_[item_index];

  try {
    TextView::ShowMessage(u8"Использован предмет: [" + item.name + u8"]" +
                          u8"!");
    // Для способностей, требующих врага
    AbilityHandler::Execute(item, state_->player_, state_->current_enemy_);
    std::cin.ignore();
    // Удаление расходуемых предметов
    if (item.id != "sake_flask") {
      inv.items_.erase(inv.items_.begin() + item_index);
    }
  } catch (const std::exception& e) {
    TextView::ShowMessage(e.what());
  }
}

void GameController::HandleAltarMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kLocationMenu;
    return;
  }

  // Получаем случайные благословения
  auto& available_blessings = state_->current_altar_blessings_;

  if (available_blessings.empty()) {
    TextView::ShowMessage(u8"У вас уже есть все доступные благословения!");
    std::cin.ignore();
    state_->current_menu_ = MenuState::kLocationMenu;
    return;
  }

  if (choice > 0 && choice <= available_blessings.size()) {
    Blessing selected_blessing = available_blessings[choice - 1];

    // Показываем детали благословения
    TextView::ShowBlessingDetails(selected_blessing, state_->player_);
    std::cin.ignore();

    // Подтверждение выбора
    TextView::ShowMessage(u8"Получить это благословение? (1 - Да, 0 - Нет): ");
    int confirm = InputHandler::GetInput();

    if (confirm == 1) {
      state_->player_.AddBlessing(selected_blessing);
      TextView::ShowMessage(u8"✨ Вы получили благословение: " +
                            selected_blessing.name);

      // Применяем пассивные эффекты
      BlessingSystem::ApplyPassiveBlessings(state_->player_,
                                            {selected_blessing});

      // Помечаем алтарь как использованный
      state_->current_location_->object_used_ = true;
      state_->current_altar_blessings_.clear();
      std::cin.ignore();
      state_->current_menu_ = MenuState::kLocationMenu;
    } else {
      state_->current_menu_ = MenuState::kAltarMenu;
    }
  } else {
    TextView::ShowMessage(u8"Некорректный выбор!");
    std::cin.ignore();
  }
}

void GameController::HandleBlessingCombatMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kCombatMenu;
    return;
  }

  // Получаем только активные благословения
  std::vector<Blessing> active_blessings = state_->player_.GetActiveBlessings();

  if (choice > 0 && choice <= active_blessings.size()) {
    Blessing& selected_blessing = active_blessings[choice - 1];

    if (BlessingSystem::CanUseBlessing(selected_blessing, state_->player_)) {
      BlessingSystem::ExecuteBlessing(selected_blessing, state_->player_,
                                      state_->current_enemy_);
      std::cin.ignore();
      state_->current_menu_ = MenuState::kCombatMenu;
    } else {
      TextView::ShowMessage(
          u8"🌀 Недостаточно Рэйки для использования благословения!");
      std::cin.ignore();
    }
  } else {
    TextView::ShowMessage(u8"Некорректный выбор!");
    std::cin.ignore();
  }
}

void GameController::HandleBlessingMenu(int choice) {
  if (choice == 0) {
    state_->current_menu_ = MenuState::kPlayerMenu;
    return;
  } else {
    std::cin.ignore();
    TextView::ShowMessage(u8"Неверный выбор!");
    return;
  }
}
