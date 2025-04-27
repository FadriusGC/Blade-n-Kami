#include "LocationLoader.h"
#include <sstream>

std::vector<Location> LocationLoader::loadFromFile(const std::string& filename) {
    std::vector<Location> locations;
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Failed to open locations file");
    }

    int currentId = -1;
    std::string line;
    std::string name, desc;
    std::vector<int> conn;
    std::string enemyID;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '[') {
            if (currentId != -1) {
                locations.emplace_back(currentId, name, desc, conn, enemyID);
                conn.clear();
            }
            currentId = std::stoi(line.substr(1, line.find(']') - 1));
        }
        else if (line.find("name=") == 0) {
            name = line.substr(5);
        }
        else if (line.find("description=") == 0) {
            desc = line.substr(12);
        }
        else if (line.find("connections=") == 0) {
            std::stringstream ss(line.substr(12));
            std::string token;
            while (getline(ss, token, ',')) {
                conn.push_back(std::stoi(token));
            }
        }
        else if (line.find("enemyID=") == 0) {
            enemyID = line.substr(8);
        }
    }

    if (currentId != -1) {
        locations.emplace_back(currentId, name, desc, conn, enemyID);
    }

    return locations;
}