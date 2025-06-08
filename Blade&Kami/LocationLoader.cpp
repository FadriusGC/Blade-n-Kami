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
    std::string name, desc, detailedDesc;
    std::vector<int> conn;
    std::string enemyID, objectID;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '[') {
            if (currentId != -1) {
                locations.emplace_back(currentId, name, desc, detailedDesc, conn, enemyID, objectID);
                conn.clear();
                detailedDesc.clear();
                objectID.clear();
                enemyID.clear();
            }
            currentId = std::stoi(line.substr(1, line.find(']') - 1));
        }
        else if (line.find("name=") == 0) {
            name = line.substr(5);
        }
        else if (line.find("description=") == 0) {
            desc = line.substr(12);
        }
        else if (line.find("detailedDescription=") == 0) {
            detailedDesc = line.substr(20);
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
        else if (line.find("objectID=") == 0) {
            objectID = line.substr(9);
        }
    }

    if (currentId != -1) {
        locations.emplace_back(currentId, name, desc, detailedDesc, conn, enemyID, objectID);
    }

    return locations;
}