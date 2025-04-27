#include "Location.h"

Location::Location(int id, const std::string& name, const std::string& desc, const std::vector<int>& conn, const std::string& enemyID)
    : id(id), name(name), description(desc), connections(conn), enemyID(enemyID) {}