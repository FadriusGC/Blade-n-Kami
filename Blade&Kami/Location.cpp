#include "Location.h"

Location::Location(int id, const std::string& name, const std::string& desc,
    const std::string& detailedDesc, const std::vector<int>& conn,
    const std::string& enemyID, const std::string& objectID)
    : id(id), name(name), description(desc), detailedDescription(detailedDesc),
    connections(conn), enemyID(enemyID), objectID(objectID), objectUsed(false) {}