//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#include "Parameter.h"

Parameter::Parameter(std::string value, const ParameterType& type) {
    this->value = value;
    this->type = type;
}

ParameterType Parameter::GetType() {
    return type;
}

std::string& Parameter::GetValue() {
    return value;
}
