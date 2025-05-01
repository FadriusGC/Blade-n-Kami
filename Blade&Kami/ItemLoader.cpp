// ItemLoader.cpp
#include "ItemLoader.h"
#include <fstream>
#include <sstream>

std::vector<Item> ItemLoader::loadFromFile(const std::string& filename) {
    std::vector<Item> items;
    std::ifstream file(filename);

    Item current;
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '[') {
            if (!current.id.empty()) {
                items.push_back(current);
                current = Item();
            }
            current.id = line.substr(1, line.find(']') - 1);
        }
        else if (line.find("name=") == 0) {
            current.name = line.substr(5);
        }
        else if (line.find("desc=") == 0) {
            current.desc = line.substr(5);
        }
        else if (line.find("cost=") == 0) {
            current.cost = std::stoi(line.substr(5));
        }
        else if (line.find("ability=") == 0) {
            current.abilityType = line.substr(8);
        }
        else if (line.find("minPower=") == 0) {
            current.minPower = std::stoi(line.substr(9));
        }
        else if (line.find("maxPower=") == 0) {
            current.maxPower = std::stoi(line.substr(9));
        }
    }

    if (!current.id.empty()) items.push_back(current);
    return items;
}