#pragma once
#include <vector>
#include <string>

class Location {
public:
    int id;
    std::string name;
    std::string description;
    std::string detailedDescription;   // Подробное описание для "Осмотреться"
    std::vector<int> connections;
    std::string enemyID;
    std::string objectID;              // ID объекта в локации (chest, merchant, altar)
    bool objectUsed;                   // Флаг использования объекта (для сундуков)
    Location(int id, const std::string& name, const std::string& desc,
        const std::string& detailedDesc, const std::vector<int>& conn,
        const std::string& enemyID, const std::string& objectID = "");
};