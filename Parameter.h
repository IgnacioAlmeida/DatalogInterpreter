//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H
#include <string>

enum class ParameterType{
    STRING,
    ID,
};
class Parameter {
private:
    ParameterType type;
    std::string value;
public:
    Parameter(std::string value, const ParameterType& type);

    ParameterType GetType();
    std::string& GetValue();
};


#endif //PROJECT_1_PARAMETER_H
