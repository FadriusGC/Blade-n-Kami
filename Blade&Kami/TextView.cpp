// TextView.cpp
#include "TextView.h"
#include <iostream>
#include <cstdlib>
#include "CombatLogic.h"
#include "BlessingSystem.h"
#include <string>
#include <sstream>
//#include <thread>
//#include <chrono>
void TextView::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TextView::showMainMenu() {
    std::cout << u8"\n=== ГЛАВНОЕ МЕНЮ ===\n"
        << u8"[1] Новая игра\n"
        << u8"[2] Загрузить игру\n"
        << u8"[3] Выход\n"
        << u8"====================\n"
        << u8"Выберите вариант: \n";
}

void TextView::showGameMenu() {
    std::cout << u8"\n=== ИГРОВОЕ МЕНЮ ===\n"
        << u8"[1] Локация\n"
        << u8"[2] Статы игрока\n"
        << u8"[3] Сохранить игру\n"
        << u8"[4] Главное меню\n"
        << u8"====================\n"
        << u8"Выберите действие: ";
}

void TextView::showMessage(const std::string& msg) {
    std::cout << u8"\n[!] " << msg << "\n";
}
void TextView::showWinMessage(const std::string& msg) {
    std::cout << u8"\n" << msg << "\n";
}
void TextView::showLocation(const Location& loc) {
    std::cout << u8"\n=== " << loc.name << " ===\n"
        << TextView::wrapText(loc.description, 50) << "\n\n";
}

void TextView::showAvailableConnections(const GameState& state) {
    std::cout << u8"====== ПЕРЕХОДЫ ======\n";
    for (int connId : state.currentLocation->connections) {
        for (const auto& loc : state.locations) {
            if (loc.id == connId) {
                std::cout << "[" << loc.id << "] " << loc.name << "\n";
                break;
            }
        }
    }
    std::cout << u8"[0] Вернуться в меню\n======================\nВведите ID локации или 0: ";
    //std::cout << "\nВведите ID локации или 'q' для выхода: ";
}

void TextView::showPlayerMenu(const Player& player) {
    std::cout << u8"\n=== ХАРАКТЕРИСТИКИ ИГРОКА ===\n"
        << u8"❤️ Здоровье: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << u8"🌀 Рейки: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << u8"🌟 Уровень: " << player.level << u8" Опыт: " << player.exp << u8"/" << player.requiredExp << "\n"
        << u8"💰 Мон Души: " << player.gold << "\n"
        << u8"💪 Сила: " << player.strength << "\n"
        << u8"🏹 Ловкость: " << player.agility << "\n"
        << u8"🧿 Дух: " << player.spirit << "\n";
    showKiBar(player.ki);
    std::cout<< "=============================" << "\n"
        << u8"[1] Прокачка характеристик\n[2] Показать статы Курай\n[3] Инвентарь\n[4] Благословения\n[0] Назад\n=============================\nВыбор: ";
}

void TextView::showKiBar(int kiValue) {
    std::cout << u8"=============================\n";
    std::cout << u8"           ☯  Ки: " << kiValue << "\n";
    std::cout << "-100 [" << generateKiBar(kiValue) << "] +100" << std::endl;
    //std::cout << u8"---------------------"
    /*std::cout << u8" ^         |         ^\n";
    std::cout << u8" -100    Нейтр    +100\n";*/
}

std::string TextView::generateKiBar(int kiValue) {
    const int barWidth = 21;
    const int centerPos = barWidth / 2;

    std::string bar = u8"";

    for (int i = 0; i < barWidth; i++) {
        if (i == centerPos && kiValue < 0) {
            bar += u8"←"; // Add "0" symbol in the middle
        }
        else if (i == centerPos && kiValue > 0) {
            bar += u8"→"; // Add "0" symbol in the middle
        }
        else if (i == centerPos && kiValue == 0) {
            bar += u8"0"; // Add "0" symbol in the middle
        }
        else if (kiValue < 0) {
            int fillPos = centerPos + (kiValue * centerPos / 100);
            if (i >= fillPos && i <= centerPos) {
                bar += u8"░"; // Заполненный блок
            }
            else {
                bar += u8"-"; // Пустой блок
            }
        }
        else if (kiValue > 0) {
            int fillPos = centerPos + (kiValue * centerPos / 100);
            if (i >= centerPos && i <= fillPos) {
                bar += u8"█"; // Заполненный блок
            }
            else {
                bar += u8"-"; // Пустой блок
            }
        }
        else {
            bar += u8"-";
        }
    }
    std::string result = bar;
    /*std::string result = u8"    Ки: " + std::to_string(kiValue) + u8"\n";
    result += u8"-100 [" + bar + u8"] +100\n";
    result += u8"      ^         |           ^\n";
    result += u8"   Зло        Нейтр      Добро";*/

    return result;
}

void TextView::showKuraiMenu(const KuraiBlade& blade) {
    std::cout << u8"\n=== МЕЧ КУРАЙ ===\n"
        << u8"Урон: " << blade.minDamage << "-" << blade.maxDamage << "\n"
        << u8"Точность: " << blade.accuracy << "\n"
        << u8"Крит: " << blade.critChance << "\n"
        << u8"=================" << "\n"
        << u8"[1] Улучшить урон\n[2] Улучшить точность\n[0] Назад\n" << "=================\n" << u8"Выбор: ";
}

void TextView::showEnemyInfo(const Enemy& enemy) {
    std::cout << "\n=== " << enemy.data.name << " ===\n"
        << u8"Здоровье: " << enemy.data.currentHealth << "/" << enemy.data.maxHealth << "\n"
        << u8"Урон: " << enemy.data.minDamage << "-" << enemy.data.maxDamage << "\n"
        << u8"Уровень: " << enemy.data.level << "\n";
}

void TextView::showEnemyList(const std::vector<EnemyData>& enemies) {
    std::cout << u8"\n=== ЗАГРУЖЕННЫЕ ВРАГИ ===";
    for (const auto& e : enemies) {
        std::cout << "\n[" << e.id << "] " << e.name
            << u8" (Уровень: " << e.level << ")";
    }
    std::cout << "\n";
}

void TextView::showEnemyDetails(const Enemy& enemy) {
    const auto& d = enemy.data;
    std::cout << "\n=== " << d.name << " ===\n"
        << u8"ID: " << d.id << "\n"
        << u8"Уровень: " << d.level << "\n"
        << u8"Здоровье: " << d.currentHealth << "/" << d.maxHealth << "\n"
        << u8"Урон: " << d.minDamage << "-" << d.maxDamage << "\n"
        << u8"Точность: " << d.accuracy * 100 << "%\n"
        << u8"Дух: " << d.spirit << "\n"
        << u8"Сила: " << d.strength << "\n"
        << u8"Способности: ";
    for (const auto& a : d.abilities) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}

void TextView::showCombatStats(const Player& player, const Enemy& enemy) {
    std::cout << u8"\n======= БОЙ =======\n"
        << u8"🥷🏻 Игрок: \n"
        << u8" ├❤️ Здоровье: " << player.currentHealth << u8"/" << player.maxHealth << u8"\n"
        << u8" ├🌀 Рэйки: " << player.currentReiki << u8"/" << player.maxReiki << "\n"
        << u8" ├💥 Урон: " << player.blade.minDamage << u8"-" << player.blade.maxDamage << "\n"
        << u8" ├🎯 Точность: " << (player.blade.accuracy * 100) << u8"%\n"
        << u8" └🍃 Уклонение: " << (player.evasion * 100) << u8"%\n"
        << u8"-------- vs --------\n" << u8"👹 Враг (" << enemy.data.name << u8"): \n"
        << u8" ├❤️ Здоровье врага: " << enemy.data.currentHealth << u8"/" << enemy.data.maxHealth << u8"\n"
        << u8" ├💥 Урон врага: " << enemy.data.minDamage << u8"-" << enemy.data.maxDamage << u8"\n"
        << u8" ├🎯 Точность врага: " << (enemy.data.accuracy * 100) << u8"%\n"
        << u8" └🍃 Уклонение врага: " << (enemy.data.evasion * 100) << u8"%\n";
}

void TextView::showCombatMenu(Player& player, Enemy& enemy) {
    std::cout << u8"==================\n[1] Атака (Шанс попадания: " << (player.blade.accuracy - enemy.data.evasion) * 100 << u8"%)" << u8"\n[2] Очищение (Шанс: " << floor(CombatLogic::calculatePurificationChance(player, enemy) * 100) << u8"%)" << u8"\n[3] Использовать предмет\n[4] Благословения\n[5] Бежать\n==================\nВыбор: ";
}

void TextView::showLevelUpMenu(const Player& player) {
    std::cout << u8"\n=== ПРОКАЧКА ХАРАКТЕРИСТИК ===\n"
        << u8"Доступно очков: " << player.availablePoints << "\n" << u8"==============================" << "\n"
        << u8"[1] Сила: " << player.strength << "\n"
        << u8"[2] Ловкость: " << player.agility << "\n"
        << u8"[3] Дух: " << player.spirit << "\n"
        << u8"[0] Выход\n"
        << u8"==============================" << "\n"
        << u8"Какую характеристику улучшить: ";
}

void TextView::showInventory(const Inventory& inv) {
    std::cout << u8"\n=== ИНВЕНТАРЬ ===\n";
    std::cout << u8"Фляга Сакэ: " << inv.sakeCharges << u8" заряда(ов)\n"
        << u8"Точильные камни: " << inv.whetstones << u8" шт.\n"
        << u8"==== Рюкзак: ====\n";

    for (const auto& item : inv.items) {
        std::cout << u8"- " << item.name << ": " << item.desc << u8"\n";
    }
    std::cout << u8"=================\n[0] Выход\n=================\nВыбор: ";
}

void TextView::showInventoryCombat(const Inventory& inv) {
    std::cout << u8"\n=== ИНВЕНТАРЬ ===\n";
    std::cout << u8"Фляга Сакэ: " << inv.sakeCharges << u8" заряда(ов)\n"
        << u8"==== Рюкзак: ====\n";

    for (size_t i = 0; i < inv.items.size(); ++i) {
        std::cout << u8"[" << i + 1 << u8"] " << inv.items[i].name << u8" - "
            << inv.items[i].desc << "\n";
    }
    std::cout << u8"=================\nВведите номер предмета для использования либо 0, чтобы вернуться в меню Бой.\n=================\nВыбор: ";
}

void TextView::showLocationMenu(const Location& loc) {
    std::cout << u8"\n=== " << loc.name << " ===\n"
        << u8"" << TextView::wrapText(loc.description, 50) << "\n\n"
        << u8"====== ДЕЙСТВИЯ ======\n"
        << u8"[1] Перемещение\n"
        << u8"[2] Осмотреться\n"
        << u8"[0] Вернуться в меню\n"
        << u8"======================\n"
        << u8"Выберите действие: ";
}

void TextView::showLocationDetails(const Location& loc) {
    std::cout << u8"\n=== ОСМОТР ЛОКАЦИИ ===\n";
    /*for (int i = 0; i < loc.detailedDescription.length(); i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << loc.detailedDescription[i];
    }
    std::cout << "\n";*/
    std::cout << TextView::wrapText(loc.detailedDescription) << "\n";

    if (!loc.objectID.empty() && !loc.objectUsed) {
        if (loc.objectID == "chest") {
            std::cout << u8"\n🎁 Вы замечаете старинный сундук в углу.\n";
        }
        // Можно добавить другие объекты позже
    }
    else {
        std::cout << u8"\nВы не замечаете каких-то более примечательных деталей здесь...\n";
    }

}

void TextView::showChestInteraction(int goldFound) {
    std::cout << u8"\n======= СУНДУК =======\n"
        << u8"🎁 Вы открываете старинный сундук...\n"
        << u8"✨ Внутри вы находите " << goldFound << u8" Мон Души!\n"
        << u8"💰 Монеты добавлены в ваш кошелек.\n"
        << u8"======================\n";
}

std::string TextView::wrapText(const std::string& text, int width) {
    std::istringstream words(text);
    std::ostringstream wrapped;
    std::string word;
    std::string line;

    while (words >> word) {
        if (line.length() + word.length() + 1 > width) { // +1 для пробела
            wrapped << line << "\n";
            line.clear();
        }

        if (!line.empty()) line += " ";
        line += word;
    }

    if (!line.empty()) wrapped << line;
    return wrapped.str();
}

void TextView::showAltarMenu(const std::vector<Blessing>& availableBlessings) {
    std::cout << u8"\n\n=== АЛТАРЬ КАМИ ===";
    for (size_t i = 0; i < availableBlessings.size(); ++i) {
        const auto& blessing = availableBlessings[i];
        std::string type = (blessing.type == BlessingType::ACTIVE)
            ? u8"⚡ АКТИВНОЕ"
            : u8"🔮 ПАССИВНОЕ";

        std::cout << u8"\n[" << i + 1 << u8"] " << blessing.name
            << u8"\n   " << type
            << u8"\n   " << blessing.description
            << u8"\n   Сила: " << blessing.basePower;

        if (blessing.type == BlessingType::ACTIVE) {
            std::cout << u8" | Рэйки: " << blessing.reikiCost;
        }
    }
    std::cout << u8"\n[0] Уйти от алтаря"
        << u8"\n======================"
        << u8"\nВыберите благословение: ";
}

void TextView::showBlessingMenu(const std::vector<Blessing>& blessings, const Player& player) {
    std::cout << u8"\n=== БЛАГОСЛОВЕНИЯ ===\n";

    if (blessings.empty()) {
        std::cout << u8"У вас нет благословений\n";
    }
    else {
        for (const auto& blessing : blessings) {
            std::string type = (blessing.type == BlessingType::ACTIVE)
                ? u8"⚡ АКТИВНОЕ"
                : u8"🔮 ПАССИВНОЕ";

            std::cout << u8"- " << blessing.name
                << u8" (" << type << u8")\n"
                << u8"  " << blessing.description << u8"\n";

            if (blessing.type == BlessingType::ACTIVE) {
                std::cout << u8"  Рэйки: " << blessing.reikiCost
                    << u8" | Сила: " << BlessingSystem::calculateModifiedPower(blessing, player) << u8"\n";
            }
            std::cout << u8"-----------------------\n";
        }
    }

    std::cout << u8"======================\n"
        << u8"Введите 0 для возвращения назад\n"
        << u8"======================\n";
}

void TextView::showBlessingDetails(const Blessing& blessing, const Player& player) {
    int modifiedPower = BlessingSystem::calculateModifiedPower(blessing, player);

    std::cout << u8"\n=== ДЕТАЛИ БЛАГОСЛОВЕНИЯ ===\n"
        << u8"Название: " << blessing.name << u8"\n"
        << u8"Описание: " << blessing.description << u8"\n"
        << u8"Тип: " << ((blessing.type == BlessingType::ACTIVE) ? u8"Активное" : u8"Пассивное") << u8"\n"
        << u8"Базовая сила: " << blessing.basePower << u8"\n"
        << u8"Модифицированная сила: " << modifiedPower << u8"\n";

    if (blessing.type == BlessingType::ACTIVE) {
        std::cout << u8"Стоимость Рэйки: " << blessing.reikiCost << u8"\n";
    }

    std::cout << u8"=============================\n"
        << u8"Нажмите Enter для продолжения...\n";
}

void TextView::showCombatBlessingsMenu(const std::vector<Blessing>& activeBlessings, const Player& player) {
    std::cout << u8"\n=== АКТИВНЫЕ БЛАГОСЛОВЕНИЯ ===\n";

    if (activeBlessings.empty()) {
        std::cout << u8"Нет доступных активных благословений\n";
    }
    else {
        for (size_t i = 0; i < activeBlessings.size(); ++i) {
            const auto& blessing = activeBlessings[i];
            bool canUse = BlessingSystem::canUseBlessing(blessing, player);
            std::string status = canUse ? u8"[ДОСТУПНО]" : u8"[НЕДОСТАТОЧНО РЭЙКИ]";
            int power = BlessingSystem::calculateModifiedPower(blessing, player);

            std::cout << u8"[" << (i + 1) << u8"] " << status << u8" " << blessing.name << u8"\n"
                << u8"  Рэйки: " << blessing.reikiCost << u8" | Сила: " << power << u8"\n";
        }
    }

    std::cout << u8"==============================\n"
        << u8"[0] Назад\n"
        << u8"==============================\n"
        << u8"Выбор: ";
}