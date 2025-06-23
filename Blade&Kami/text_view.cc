#include "text_view.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "blessing_system.h"
#include "combat_logic.h"

void TextView::ClearScreen() {
  std::cout << "\033[2J\033[1;1H";  // <- ANSI escape sequence (code) Потому что
                                    // вам не понравилось system("cls")
  // #ifdef _WIN32
  //   system("cls");
  // #else
  //   system("clear");
  // #endif
}

void TextView::ShowMainMenu() {
  std::cout << u8"\n=== ГЛАВНОЕ МЕНЮ ===\n"
            << u8"[1] Новая игра\n"
            << u8"[2] Загрузить игру\n"
            << u8"[3] Выход\n"
            << u8"====================\n"
            << u8"Выберите вариант: \n";
}

void TextView::ShowGameMenu() {
  std::cout << u8"\n=== ИГРОВОЕ МЕНЮ ===\n"
            << u8"[1] Локация\n"
            << u8"[2] Статы игрока\n"
            << u8"[3] Сохранить игру\n"
            << u8"[4] Главное меню\n"
            << u8"====================\n"
            << u8"Выберите действие: ";
}

void TextView::ShowMessage(const std::string& msg) {
  std::cout << u8"\n[!] " << msg << "\n";
}
void TextView::ShowWinMessage(const std::string& msg) {
  std::cout << u8"\n" << msg << "\n";
}
void TextView::ShowLocation(const Location& loc) {
  std::cout << u8"\n=== " << loc.name_ << " ===\n"
            << TextView::WrapText(loc.description_, 50) << "\n\n";
}

void TextView::ShowAvailableConnections(const GameState& state) {
  std::cout << u8"====== ПЕРЕХОДЫ ======\n";
  for (int conn_id : state.current_location_->connections_) {
    for (const auto& loc : state.locations_) {
      if (loc.id_ == conn_id) {
        std::cout << "[" << loc.id_ << "] " << loc.name_ << "\n";
        break;
      }
    }
  }
  std::cout << u8"[0] Вернуться в меню\n======================\nВведите ID "
               u8"локации или 0: ";
  // std::cout << "\nВведите ID локации или 'q' для выхода: ";
}

void TextView::ShowPlayerMenu(const Player& player) {
  std::cout << u8"\n=== ХАРАКТЕРИСТИКИ ИГРОКА ===\n"
            << u8"❤️ Здоровье: " << player.current_health_ << "/"
            << player.max_health_ << "\n"
            << u8"🌀 Рейки: " << player.current_reiki_ << "/"
            << player.base_reiki_ << "\n"
            << u8"🌟 Уровень: " << player.level_ << u8" Опыт: " << player.exp_
            << u8"/" << player.required_exp_ << "\n"
            << u8"💰 Мон Души: " << player.gold_ << "\n"
            << u8"💪 Сила: " << player.strength_ << "\n"
            << u8"🏹 Ловкость: " << player.agility_ << "\n"
            << u8"🧿 Дух: " << player.spirit_ << "\n";
  ShowKiBar(player.ki_);
  std::cout << "=============================" << "\n"
            << u8"[1] Прокачка характеристик\n[2] Показать статы Курай\n[3] "
               u8"Инвентарь\n[4] Благословения\n[0] "
               u8"Назад\n=============================\nВыбор: ";
}

void TextView::ShowKiBar(int kiValue) {
  std::cout << u8"=============================\n";
  std::cout << u8"           ☯  Ки: " << kiValue << "\n";
  std::cout << "-100 [" << GenerateKiBar(kiValue) << "] +100" << std::endl;
}

std::string TextView::GenerateKiBar(int kiValue) {
  const int bar_width = 21;
  const int center_pos = bar_width / 2;

  std::string bar = u8"";

  for (int i = 0; i < bar_width; i++) {
    if (i == center_pos && kiValue < 0) {
      bar += u8"←";
    } else if (i == center_pos && kiValue > 0) {
      bar += u8"→";
    } else if (i == center_pos && kiValue == 0) {
      bar += u8"0";
    } else if (kiValue < 0) {
      int fill_pos = center_pos + (kiValue * center_pos / 100);
      if (i >= fill_pos && i <= center_pos) {
        bar += u8"░";
      } else {
        bar += u8"-";
      }
    } else if (kiValue > 0) {
      int fillPos = center_pos + (kiValue * center_pos / 100);
      if (i >= center_pos && i <= fillPos) {
        bar += u8"█";
      } else {
        bar += u8"-";
      }
    } else {
      bar += u8"-";
    }
  }
  std::string result = bar;
  return result;
}

void TextView::ShowKuraiMenu(const KuraiBlade& blade) {
  std::cout << u8"\n=== МЕЧ КУРАЙ ===\n"
            << u8"Урон: " << blade.min_damage_ << "-" << blade.max_damage_
            << "\n"
            << u8"Точность: " << blade.accuracy_ << "\n"
            << u8"Шанс крита: " << blade.crit_chance_ * 100 << "%\n"
            << u8"Духовная ёмкость: " << blade.spirit_capacity_ << "\n"
            << u8"=================" << "\n"
            << u8"[1] Улучшить урон\n[2] Улучшить точность\n[3] Улучшить шанс "
               u8"крита\n[4] Улучшить духовную ёмкость\n[0] Назад\n"
            << "=================\n"
            << u8"Выбор: ";
}

void TextView::ShowEnemyInfo(const Enemy& enemy) {
  std::cout << "\n=== " << enemy.data_.name << " ===\n"
            << u8"Здоровье: " << enemy.data_.current_health << "/"
            << enemy.data_.max_health << "\n"
            << u8"Урон: " << enemy.data_.min_damage << "-"
            << enemy.data_.max_damage << "\n"
            << u8"Уровень: " << enemy.data_.level << "\n";
}

void TextView::ShowEnemyList(const std::vector<EnemyData>& enemies) {
  std::cout << u8"\n=== ЗАГРУЖЕННЫЕ ВРАГИ ===";
  for (const auto& enemy : enemies) {
    std::cout << "\n[" << enemy.id << "] " << enemy.name << u8" (Уровень: "
              << enemy.level << ")";
  }
  std::cout << "\n";
}

void TextView::ShowEnemyDetails(const Enemy& enemy) {
  const auto& data = enemy.data_;
  std::cout << "\n=== " << data.name << " ===\n"
            << u8"ID: " << data.id << "\n"
            << u8"Уровень: " << data.level << "\n"
            << u8"Здоровье: " << data.current_health << "/" << data.max_health
            << "\n"
            << u8"Урон: " << data.min_damage << "-" << data.max_damage << "\n"
            << u8"Точность: " << data.accuracy * 100 << "%\n"
            << u8"Дух: " << data.spirit << "\n"
            << u8"Сила: " << data.strength << "\n"
            << u8"Способности: ";
  for (const auto& abilities : data.abilities) {
    std::cout << abilities << " ";
  }
  std::cout << "\n";
}

void TextView::ShowCombatStats(const Player& player, const Enemy& enemy) {
  std::cout << u8"\n======= БОЙ =======\n"
            << u8"🥷🏻 Игрок: \n"
            << u8" ├❤️ Здоровье: " << player.current_health_ << u8"/"
            << player.max_health_ << u8"\n"
            << u8" ├🌀 Рэйки: " << player.current_reiki_ << u8"/"
            << player.max_reiki_ << "\n"
            << u8" ├💥 Урон: " << player.GetMinDamage() << u8"-"
            << player.GetMaxDamage() << "\n"
            << u8" ├🎯 Точность: " << (player.GetAccuracy() * 100) << u8"%\n"
            << u8" └🍃 Уклонение: " << (player.evasion_ * 100) << u8"%\n"
            << u8"-------- vs --------\n"
            << u8"👹 Враг (" << enemy.data_.name << u8"): \n"
            << u8" ├❤️ Здоровье врага: " << enemy.data_.current_health << u8"/"
            << enemy.data_.max_health << u8"\n"
            << u8" ├💥 Урон врага: " << enemy.data_.min_damage << u8"-"
            << enemy.data_.max_damage << u8"\n"
            << u8" ├🎯 Точность врага: " << (enemy.data_.accuracy * 100)
            << u8"%\n"
            << u8" └🍃 Уклонение врага: " << (enemy.data_.evasion * 100)
            << u8"%\n";
}

void TextView::ShowCombatMenu(Player& player, Enemy& enemy) {
  std::cout << u8"==================\n[1] Атака (Шанс попадания: "
            << (player.blade_.accuracy_ - enemy.data_.evasion) * 100 << u8"%)"
            << u8"\n[2] Очищение (Шанс: "
            << floor(CombatLogic::CalculatePurificationChance(player, enemy) *
                     100)
            << u8"%)"
            << u8"\n[3] Использовать предмет\n[4] Благословения\n[5] "
               u8"Бежать\n==================\nВыбор: ";
}

void TextView::ShowLevelUpMenu(const Player& player) {
  std::cout << u8"\n=== ПРОКАЧКА ХАРАКТЕРИСТИК ===\n"
            << u8"Доступно очков: " << player.available_points_ << "\n"
            << u8"==============================" << "\n"
            << u8"[1] Сила: " << player.strength_ << "\n"
            << u8"[2] Ловкость: " << player.agility_ << "\n"
            << u8"[3] Дух: " << player.spirit_ << "\n"
            << u8"[0] Выход\n"
            << u8"==============================" << "\n"
            << u8"Какую характеристику улучшить: ";
}

void TextView::ShowInventory(const Inventory& inv) {
  std::cout << u8"\n=== ИНВЕНТАРЬ ===\n";
  std::cout << u8"Фляга Сакэ: " << inv.sake_charges_ << u8" заряда(ов)\n"
            << u8"Точильные камни: " << inv.whetstones_ << u8" шт.\n"
            << u8"==== Рюкзак: ====\n";

  for (const auto& item : inv.items_) {
    std::cout << u8"- " << item.name << ": " << item.desc << u8"\n";
  }
  std::cout << u8"=================\n[0] Выход\n=================\nВыбор: ";
}

void TextView::ShowInventoryCombat(const Inventory& inv) {
  std::cout << u8"\n=== ИНВЕНТАРЬ ===\n";
  std::cout << u8"Фляга Сакэ: " << inv.sake_charges_ << u8" заряда(ов)\n"
            << u8"==== Рюкзак: ====\n";

  for (size_t i = 0; i < inv.items_.size(); ++i) {
    std::cout << u8"[" << i + 1 << u8"] " << inv.items_[i].name << u8" - "
              << inv.items_[i].desc << "\n";
  }
  std::cout
      << u8"=================\nВведите номер предмета для использования либо "
         u8"0, чтобы вернуться в меню Бой.\n=================\nВыбор: ";
}

void TextView::ShowLocationMenu(const Location& loc) {
  std::cout << u8"\n=== " << loc.name_ << " ===\n"
            << u8"" << TextView::WrapText(loc.description_, 50) << "\n\n"
            << u8"====== ДЕЙСТВИЯ ======\n"
            << u8"[1] Перемещение\n"
            << u8"[2] Осмотреться\n"
            << u8"[0] Вернуться в меню\n"
            << u8"======================\n"
            << u8"Выберите действие: ";
}

void TextView::ShowLocationDetails(const Location& loc) {
  std::cout << u8"\n=== ОСМОТР ЛОКАЦИИ ===\n";
  std::cout << TextView::WrapText(loc.detailed_description_) << "\n";

  if (!loc.object_id_.empty() && !loc.object_used_) {
    if (loc.object_id_ == "chest") {
      std::cout << u8"\n🎁 Вы замечаете старинный сундук в углу.\n";
    }
    // Можно добавить другие объекты позже
  } else {
    std::cout << u8"\nВы не замечаете каких-то более примечательных деталей "
                 u8"здесь...\n";
  }
}

void TextView::ShowChestInteraction(int goldFound,
                                    const std::string dropped_item) {
  if (dropped_item != "") {
    std::cout << u8"\n======= СУНДУК =======\n"
              << u8"🎁 Вы открываете старинный сундук...\n"
              << u8"✨ Внутри вы находите " << goldFound << u8" Мон Души и "
              << dropped_item << u8"!\n"
              << u8"💰 Монеты добавлены в ваш кошелек.\n"
              << u8"📦 " << dropped_item << u8" добавлен в ваш рюкзак.\n"
              << u8"======================\n";
  } else {
    std::cout << u8"\n======= СУНДУК =======\n"
              << u8"🎁 Вы открываете старинный сундук...\n"
              << u8"✨ Внутри вы находите " << goldFound << u8" Мон Души!\n"
              << u8"💰 Монеты добавлены в ваш кошелек.\n"
              << u8"======================\n";
  }
}

std::string TextView::WrapText(const std::string& text, int width) {
  std::istringstream words(text);
  std::ostringstream wrapped;
  std::string word;
  std::string line;

  while (words >> word) {
    if (line.length() + word.length() + 1 > width) {  // +1 для пробела
      wrapped << line << "\n";
      line.clear();
    }

    if (!line.empty()) line += " ";
    line += word;
  }

  if (!line.empty()) wrapped << line;
  return wrapped.str();
}

void TextView::ShowAltarMenu(const std::vector<Blessing>& available_blessings,
                             const Player& player) {
  std::cout << u8"=== АЛТАРЬ КАМИ ===\n-------------------";
  for (size_t i = 0; i < available_blessings.size(); ++i) {
    const auto& blessing = available_blessings[i];
    std::string type = (blessing.type == BlessingType::kActive)
                           ? u8"⚡ АКТИВНОЕ"
                           : u8"🔮 ПАССИВНОЕ";
    ModifiedPower power =
        BlessingSystem::CalculateModifiedPower(blessing, player);
    std::string power_desc = TextView::GeneratePowerDescription(
        blessing.ability, power.min, power.max);

    std::cout << u8"\n[" << i + 1 << u8"] " << blessing.name << u8"\n   "
              << type << u8"\n   "
              << TextView::WrapText(blessing.description, 80);
    if (blessing.type == BlessingType::kActive) {
      std::cout << u8"\n   Рэйки: " << blessing.reiki_cost;
    }
    std::cout << u8"\n   " << TextView::WrapText(power_desc, 80);

    std::cout << "\n-------------------";
  }
  std::cout << u8"\n[0] Уйти от алтаря" << u8"\n==================="
            << u8"\nВыберите благословение: ";
}

void TextView::ShowBlessingMenu(const std::vector<Blessing>& blessings,
                                const Player& player) {
  std::cout << u8"\n=== БЛАГОСЛОВЕНИЯ ===\n";

  if (blessings.empty()) {
    std::cout << u8"У вас нет благословений\n";
  } else {
    for (const auto& blessing : blessings) {
      ModifiedPower power =
          BlessingSystem::CalculateModifiedPower(blessing, player);
      std::string power_desc = TextView::GeneratePowerDescription(
          blessing.ability, power.min, power.max);

      std::string type = (blessing.type == BlessingType::kActive)
                             ? u8"⚡ АКТИВНОЕ"
                             : u8"🔮 ПАССИВНОЕ";

      std::cout << u8"- " << blessing.name << u8"\n  " << type << u8"\n"
                << u8"  " << TextView::WrapText(blessing.description, 80)
                << u8"\n";

      if (blessing.type == BlessingType::kActive) {
        std::cout << u8"  Рэйки: " << blessing.reiki_cost << u8"\n  "
                  << TextView::WrapText(power_desc, 80) << u8"\n";
      }
      std::cout << u8"----------------------\n";
    }
  }

  std::cout << u8"======================\n"
            << u8"Введите 0 для возвращения назад\n"
            << u8"======================\n";
}

void TextView::ShowBlessingDetails(const Blessing& blessing,
                                   const Player& player) {
  ModifiedPower power =
      BlessingSystem::CalculateModifiedPower(blessing, player);
  std::string power_desc = TextView::GeneratePowerDescription(
      blessing.ability, power.min, power.max);

  std::cout << u8"\n=== ДЕТАЛИ БЛАГОСЛОВЕНИЯ ===\n"
            << u8"Название: " << blessing.name << u8"\n"
            << u8"Ками: " << blessing.kami << u8", "
            << BlessingSystem::GetKamiType(blessing) << u8"\n"
            << u8"----------------------------\n"
            << u8"Описание: " << TextView::WrapText(blessing.description, 80)
            << u8"\n"
            << u8"----------------------------\n"
            << u8"Тип: "
            << ((blessing.type == BlessingType::kActive) ? u8"Активное"
                                                         : u8"Пассивное")
            << u8"\n"
            << u8"" << power_desc << u8"\n";

  if (blessing.type == BlessingType::kActive) {
    std::cout << u8"Стоимость Рэйки: " << blessing.reiki_cost << u8"\n";
  }

  std::cout << u8"============================\n";
}

void TextView::ShowCombatBlessingsMenu(
    const std::vector<Blessing>& active_blessings, const Player& player) {
  std::cout << u8"\n=== АКТИВНЫЕ БЛАГОСЛОВЕНИЯ ===\n";

  if (active_blessings.empty()) {
    std::cout << u8"Нет доступных активных благословений\n";
  } else {
    std::cout << "------------------------------\n";
    for (size_t i = 0; i < active_blessings.size(); ++i) {
      const auto& blessing = active_blessings[i];
      bool can_use = BlessingSystem::CanUseBlessing(blessing, player);
      std::string status = can_use ? u8"[ДОСТУПНО]" : u8"[НЕДОСТАТОЧНО РЭЙКИ]";
      ModifiedPower power =
          BlessingSystem::CalculateModifiedPower(blessing, player);
      std::string power_desc = TextView::GeneratePowerDescription(
          blessing.ability, power.min, power.max);
      // int power = BlessingSystem::calculateModifiedPower(blessing, player);

      std::cout << u8"[" << (i + 1) << u8"] " << status << u8" "
                << blessing.name << u8"\n"
                << u8"  Рэйки: " << blessing.reiki_cost << u8"\n  "
                << TextView::WrapText(power_desc, 80)
                << u8"\n------------------------------\n";
    }
  }

  std::cout << u8"==============================\n"
            << u8"[0] Назад\n"
            << u8"==============================\n"
            << u8"Выбор: ";
}

std::string TextView::GeneratePowerDescription(const std::string& ability,
                                               int min_power, int max_power) {
  if (ability == "heal") {
    return u8"Эффект: Восстанавливает " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) + u8" здоровья";
  } else if (ability == "damage") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) + u8" урона";
  } else if (ability == "sun_strike") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) + u8" урона + 10% от макс. здоровья";
  } else if (ability == "touch_of_death") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) +
           u8" урона + 30% от недостающего здоровья врага";
  } else if (ability == "ravens_feast") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) +
           u8" урона и исцеляет на 30% от нанесенного урона";
  } else if (ability == "ruthless_cuts") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) +
           u8" урона + 20% от вашего недостающего здоровья";
  } else if (ability == "dragon_technique_calm") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) +
           u8" урона + 0.5 за каждую потраченную единицу Рэйки";
  } else if (ability == "lunar_dance") {
    return u8"Эффект: Наносит " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) +
           u8" урона + 20% от вашей максимальной Рэйки";
  } else if (ability == "reiki_restore") {
    return u8"Эффект: Восстанавливает " + std::to_string(min_power) + u8"-" +
           std::to_string(max_power) + u8" Рэйки";
  } else if (ability == "purification_boost") {
    return u8"Эффект: Увеличивает шанс очищения на 50%";
  }
  // Добавьте другие способности по аналогии

  return u8"Сила/Увеличение параметров: " + std::to_string(min_power) + u8"-" +
         std::to_string(max_power);
}

void TextView::ShowEvilEnding(GameState& state) {
  std::cout << std::string(30, '=') + "\n";
  std::cout << u8"🌑 КОНЦОВКА: ПУТЬ ТЬМЫ 🌑\n";
  std::cout << std::string(30, '=') + "\n";

  std::cout << TextView::WrapText(
      u8"Ямато-но-ороти повержен, но какой ценой... Темная сила древнего змея "
      "просочилась в вашу душу. Клинок Курай почернел от пролитой крови, а "
      "ваше сердце наполнилось жаждой разрушения. Проклятые духи леса "
      "действительно исчезли, но не потому, что обрели покой — они бежали в "
      "ужасе от того, кем вы стали. Теперь вы — новый источник тьмы в этих "
      "землях. Лес затих. Птицы больше не поют. Даже ветер боится потревожить "
      "нового владыку этих проклятых земель. Ваше имя станет легендой… "
      "легендой о тьме...");
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\n💀 Вы стали тем, с чем пришли бороться. 💀\n";
  std::cout << u8"🌑 КИ: " + std::to_string(state.player_.ki_) + u8" 🌑";
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\nНажмите любую клавишу, чтобы выйти.";
}

void TextView::ShowGoodEnding(GameState& state) {
  std::cout << std::string(30, '=') + "\n";
  std::cout << u8"🌞 КОНЦОВКА: ПУТЬ СВЕТА 🌞\n";
  std::cout << std::string(30, '=') + "\n";

  std::cout << TextView::WrapText(
      u8"Ваш клинок пронзает сердце Ямато-но-ороти, и древний змей издает "
      "последний, предсмертный рык. Его темная сила рассеивается, как туман на "
      "рассвете. Проклятие, тяготевшее над лесом веками, наконец снято. Духи, "
      "которых вы очистили в своем путешествии, обретают долгожданный покой. "
      "Лес начинает исцеляться. Клинок Курай сияет чистым светом, отражая вашу "
      "незапятнанную душу. Ваше сердце наполнено умиротворением — вы выполнили "
      "свой долг, не запятнав себя излишней жестокостью. Лес оживает: птицы "
      "вновь поют, цветы распускаются, а чистые ручьи журчат песни "
      "благодарности. Вы стали настоящим героем, защитником света.");
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\n✨ Баланс восстановлен. Мир спасен. ✨\n";
  std::cout << u8"🌞 КИ: " + std::to_string(state.player_.ki_) + u8" 🌞";
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\nНажмите любую клавишу, чтобы выйти.";
}

void TextView::ShowBloodAndSakeEnding(GameState& state) {
  std::cout << std::string(30, '=') + "\n";
  std::cout << u8"⚔️ КОНЦОВКА: КРОВЬ И САКЭ ⚔️\n";
  std::cout << std::string(30, '=') + "\n";

  std::cout << TextView::WrapText(
      u8"Без помощи духов и благословений богов, полагаясь лишь на собственную "
      "силу и мастерство клинка, вы одолели самого Ямато-но-ороти. Это подвиг "
      "истинного мастера! Ваш путь был усеян кровью врагов и пропитан горечью "
      "сакэ, которое притупляло боль от ран. Никто не помогал вам — ни боги, "
      "ни духи предков. Только вы и ваш клинок. Клинок Курай, закаленный в "
      "бесчисленных битвах, стал легендарным оружием. Ваше имя войдет в "
      "историю как имя воина, который не нуждался в чужой силе. Лес очищен, "
      "проклятие снято, но какой ценой... Шрамы на вашем теле и душе останутся "
      "навсегда. Вы — одинокий волк, мастер клинка, легенда во плоти.\n");
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\n🍶 Путь одиночки завершен. Честь превыше всего. ⚔️\n";
  std::cout << u8"🩸 УРОВЕНЬ: " + std::to_string(state.player_.level_) +
                   u8" | КИ: " + std::to_string(state.player_.ki_) + u8" 🩸\n";
  std::cout << u8"⚔️ Без благословений, только сила воли! ⚔️";
  std::cout << "\n" + std::string(30, '=');
  std::cout << u8"\nНажмите любую клавишу, чтобы выйти.";
}
