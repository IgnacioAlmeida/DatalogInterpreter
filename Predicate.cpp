//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#include "Predicate.h"
Predicate::Predicate(std::string id, std::vector<Parameter> parameter) {
    this->id = id;
    this->parameters = parameter;
}

std::string Predicate::ToString() {
    std::string output = id + "(" + parameters.at(0).GetValue();
    for (unsigned int i = 1; i < parameters.size(); i++){
        output += "," + parameters.at(i).GetValue();
    }
    output += ")";

    return output;
}

std::string& Predicate::GetId(){
    return id;
}

std::vector<Parameter> Predicate::GetParameters() {
    return parameters;
}