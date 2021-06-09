//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H
#include <iostream>
#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple(){}
    Tuple(std::vector<std::string> values) {this->values = values;}
    bool operator < (const Tuple& other) const;
    std::vector<std::string> GetValues ()const{return values;}
    std::string ToString();
};


#endif //PROJECT_1_TUPLE_H
