#ifndef BLESSING_H_
#define BLESSING_H_

#include <string>

enum class BlessingType {
  kActive,  // Требует активации в бою
  kPassive  // Постоянный эффект
};

struct Blessing {
  std::string id;
  std::string name;
  std::string description;
  std::string kami;
  std::string kami_type;
  BlessingType type;
  std::string ability;  // Название способности для AbilityHandler
  int base_power;       // Базовая сила (модифицируется Ки/Духом)
  int reiki_cost;       // Стоимость в Рэйки (0 для пассивных)

  Blessing() = default;

  Blessing(const std::string& id, const std::string& name,
           const std::string& desc, const std::string& kami,
           const std::string kami_type, BlessingType type,
           const std::string& ability, int base_power, int reiki_cost)
      : id(id),
        name(name),
        description(desc),
        kami(kami),
        kami_type(kami_type),
        type(type),
        ability(ability),
        base_power(base_power),
        reiki_cost(reiki_cost) {}
};

#endif  // BLESSING_H_
