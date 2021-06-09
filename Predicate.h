//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {
private:
    std::string id;
    std::vector<Parameter> parameters;
public:
    Predicate(std::string id, std::vector<Parameter> parameter);
    Predicate(){};


    std::string ToString();
    std::string& GetId();
    std::vector<Parameter> GetParameters();

};


#endif //PROJECT_1_PREDICATE_H
