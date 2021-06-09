//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#include "Tuple.h"

bool Tuple::operator< (const Tuple& otherTuple) const{
    return values < otherTuple.values;
}

std::string Tuple::ToString() {
    std::string output;

    for(unsigned int i = 0; i < values.size(); i++){
        output += values.at(i) + " ";
    }

    return output;
}