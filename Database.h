//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#ifndef DATALOGINTERPRETER_DATABASE_H
#define DATALOGINTERPRETER_DATABASE_H
#include <map>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation> database;
public:
    Database(){}
    void SetDatabase(std::string id, Relation);
    std::map<std::string, Relation>& GetDatabase(){return database;}
    Relation* GetRelationPointer(std::string value){return &database.at(value);}
    Relation GetRelation(std::string value){return database.at(value);}
    std::string ToString();
    int DatabaseCounter();
};


#endif //DATALOGINTERPRETER_DATABASE_H
