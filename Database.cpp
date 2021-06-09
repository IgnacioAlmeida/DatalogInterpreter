//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#include "Database.h"

void Database::SetDatabase(std::string id, Relation relation) {
    database[id] = relation;
}

std::string Database::ToString() {
    std::string output;
    for(std::map<std::string, Relation>::iterator print = database.begin(); print != database.end(); print++){
        output += (print->first + print->second.ToString() + "\n");
    }
    return output;
}

int Database::DatabaseCounter() {
    int initialCount = 0;

    for(std::map<std::string, Relation>::iterator it = database.begin(); it != database.end(); it++){
        initialCount += it->second.GetRows().size();
    }

    return initialCount;
}