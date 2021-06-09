//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#include "Header.h"

std::string Header::ToString() {
    std::string output = "(";

    for(int unsigned i =0 ; i < parameters.size(); i++){
        if((std::size_t)i < parameters.size() - 1) {
            output += parameters.at(i) + ",";
        }
        else {
            output += parameters.at(i);
        }
    }
    output += ")";
    return output;
}