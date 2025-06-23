#ifndef ITEM_H_
#define ITEM_H_

#include <string>

struct Item {
  std::string id;
  std::string name;
  std::string desc;
  int cost = 0;
  std::string ability;
  int min_power = 0;
  int max_power = 0;

  Item() = default;
  Item(const std::string& id, const std::string& name, const std::string& desc,
       int cost, const std::string& ability, int min_p, int max_p)
      : id(id),
        name(name),
        desc(desc),
        cost(cost),
        ability(ability),
        min_power(min_p),
        max_power(max_p) {}
};

#endif  // ITEM_H_
